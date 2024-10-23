import numpy as np
import pandas as pd
import yfinance as yf
from scipy.optimize import brute
import matplotlib.pyplot as plt
from datetime import datetime, timedelta

class VectorizedBacktester:
    """
    Base class for vectorized backtesting with real-time data from yfinance.
    
    Attributes
    ----------
    symbol: str
        Trading symbol (e.g., 'AAPL', 'MSFT')
    start: str
        start date for data import (YYYY-MM-DD)
    end: str
        end date for data import (YYYY-MM-DD)
    amount: float
        amount to be invested either long or short
    tc: float
        proportional transaction costs (e.g., 0.5% = 0.005)
    """
    
    def __init__(self, symbol, start, end, amount, tc):
        self.symbol = symbol
        self.start = start
        self.end = end
        self.amount = amount
        self.tc = tc
        self.results = None
        self.get_data()
        
    def get_data(self):
        """
        Imports the data from yfinance.
        """
        ticker = yf.Ticker(self.symbol)
        raw = ticker.history(start=self.start, end=self.end, interval="1d")
        raw['returns'] = np.log(raw['Close'] / raw['Close'].shift(1))
        raw['price'] = raw['Close']
        self.data = raw
        
    def set_parameters(self, **kwargs):
        """
        Sets one or more parameters.
        """
        for key in kwargs.keys():
            setattr(self, key, kwargs[key])
            
    def test_strategy(self):
        """
        Backtests the trading strategy and calculates comprehensive metrics.
        """
        data = self.data.copy().dropna()
        data['position'] = self.generate_signals()
        data['strategy'] = data['position'].shift(1) * data['returns']
        data['trades'] = data['position'].diff().fillna(0).abs()
        data['strategy'] = data['strategy'] - data['trades'] * self.tc
        
        # Cumulative returns
        data['creturns'] = data['returns'].cumsum().apply(np.exp)
        data['cstrategy'] = data['strategy'].cumsum().apply(np.exp)
        
        # Calculate daily strategy value
        data['strategy_value'] = self.amount * data['cstrategy']
        data['market_value'] = self.amount * data['creturns']
        
        # Calculate drawdowns
        data['peak'] = data['strategy_value'].cummax()
        data['drawdown'] = (data['strategy_value'] - data['peak']) / data['peak']
        
        # Store results
        self.results = data
        
        # Calculate comprehensive metrics
        metrics = self.calculate_metrics()
        
        return metrics
    
    def calculate_metrics(self):
        """
        Calculate comprehensive trading metrics.
        """
        if self.results is None:
            return None
            
        data = self.results
        strategy_ret = self.results['strategy']
        
        # Basic Metrics
        total_return = (data['strategy_value'].iloc[-1] - self.amount) / self.amount
        market_return = (data['market_value'].iloc[-1] - self.amount) / self.amount
        
        # Risk metrics
        volatility = np.std(strategy_ret) * np.sqrt(252)
        sharpe_ratio = np.mean(strategy_ret) / np.std(strategy_ret) * np.sqrt(252)
        sortino_ratio = np.mean(strategy_ret) / np.std(strategy_ret[strategy_ret < 0]) * np.sqrt(252)
        
        # Drawdown metrics
        max_drawdown = self.results['drawdown'].min()
        avg_drawdown = self.results['drawdown'].mean()
        
        # Trading metrics
        n_trades = self.results['trades'].sum() / 2
        winning_trades = len(strategy_ret[strategy_ret > 0])
        losing_trades = len(strategy_ret[strategy_ret < 0])
        win_rate = winning_trades / (winning_trades + losing_trades) if n_trades > 0 else 0
        
        metrics = {
            'Total Return': total_return,
            'Market Return': market_return,
            'Excess Return': total_return - market_return,
            'Annual Volatility': volatility,
            'Sharpe Ratio': sharpe_ratio,
            'Sortino Ratio': sortino_ratio,
            'Max Drawdown': max_drawdown,
            'Average Drawdown': avg_drawdown,
            'Number of Trades': n_trades,
            'Win Rate': win_rate,
            'Transaction Costs': self.results['trades'].sum() * self.tc * self.amount,
            'Profit/Loss': self.results['strategy_value'].iloc[-1] - self.amount
        }
        
        return metrics

    def optimize_parameters(self, param_grid, metric='Total Return'):
        """
        Finds global maximum given the parameter ranges.
        
        Parameters
        ----------
        param_grid: dict
            with parameter names as keys and tuple of the form
            (start, end, step size) as values
        metric: str
            performance metric to be optimized
        """
        def optimize_objective(p):
            self.set_parameters(**{list(param_grid.keys())[i]: p[i] 
                                 for i in range(len(p))})
            metrics = self.test_strategy()
            return -metrics[metric]
            
        opt = brute(optimize_objective,
                    tuple(param_grid.values()),
                    finish=None)
                    
        final_params = {list(param_grid.keys())[i]: opt[i] 
                       for i in range(len(opt))}
        self.set_parameters(**final_params)
        metrics = self.test_strategy()
        
        return final_params, metrics

    def enhanced_plot_results(self):
        """
        Enhanced plotting function that shows more strategy details.
        """
        if self.results is None:
            print('No results to plot yet. Run test_strategy() first.')
            return
            
        # Create figure with 4 subplots
        fig, (ax1, ax2, ax3, ax4) = plt.subplots(4, 1, figsize=(15, 20))
        
        # 1. Price and Indicators
        if isinstance(self, MovingAverageCrossBacktester):
            # For Moving Average strategy
            ax1.plot(self.data.index, self.data['price'], label='Price', alpha=0.7)
            ax1.plot(self.data.index, self.data['SMA1'], label=f'SMA{self.sma1}', linestyle='--')
            ax1.plot(self.data.index, self.data['SMA2'], label=f'SMA{self.sma2}', linestyle='--')
            ax1.set_title('Price and Moving Averages')
        elif isinstance(self, RSIBacktester):
            # For RSI strategy
            ax1.plot(self.data.index, self.data['price'], label='Price')
            ax1_twin = ax1.twinx()
            ax1_twin.plot(self.data.index, self.data['RSI'], label='RSI', color='orange')
            ax1_twin.axhline(y=self.upper_bound, color='r', linestyle='--', alpha=0.5)
            ax1_twin.axhline(y=self.lower_bound, color='g', linestyle='--', alpha=0.5)
            ax1_twin.set_ylim(0, 100)
            ax1_twin.set_ylabel('RSI')
        ax1.legend(loc='upper left')
        ax1.set_ylabel('Price ($)')
        
        # 2. Strategy vs Market Value
        self.results[['strategy_value', 'market_value']].plot(ax=ax2, 
                                                          title='Strategy vs Market Performance')
        ax2.set_ylabel('Portfolio Value ($)')
        
        # 3. Drawdowns
        self.results['drawdown'].plot(ax=ax3, title='Strategy Drawdowns', color='red')
        ax3.set_ylabel('Drawdown (%)')
        
        # 4. Position Changes with Trading Volume
        ax4.plot(self.results.index, self.results['position'], label='Position')
        # Highlight trading points
        trades = self.results['trades'] > 0
        if trades.any():
            ax4.scatter(self.results.index[trades], 
                      self.results['position'][trades],
                      color='red', label='Trades', zorder=5)
        ax4.set_title('Position Changes and Trading Points')
        ax4.set_ylabel('Position (-1, 0, 1)')
        ax4.legend()
        
        plt.tight_layout()
        plt.show()


class MovingAverageCrossBacktester(VectorizedBacktester):
    """
    Class for the vectorized backtesting of Moving Average Crossover strategy.
    """
    
    def __init__(self, symbol, start, end, amount, tc, sma1, sma2):
        self.sma1 = int(sma1)
        self.sma2 = int(sma2)
        super().__init__(symbol, start, end, amount, tc)
        
    def generate_signals(self):
        data = self.data.copy()
        data['SMA1'] = data['price'].rolling(int(self.sma1)).mean()
        data['SMA2'] = data['price'].rolling(int(self.sma2)).mean()
        data['position'] = np.where(data['SMA1'] > data['SMA2'], 1, -1)
        self.data = data  # Save for plotting
        return data['position']
    
    def set_parameters(self, **kwargs):
        """
        Override set_parameters to ensure SMA values are integers
        """
        for key, value in kwargs.items():
            if key in ['sma1', 'sma2']:
                setattr(self, key, int(value))
            else:
                setattr(self, key, value)


class RSIBacktester(VectorizedBacktester):
    """
    Class for the vectorized backtesting of RSI strategy.
    """
    
    def __init__(self, symbol, start, end, amount, tc, rsi_period=14, 
                 upper_bound=70, lower_bound=30):
        self.rsi_period = rsi_period
        self.upper_bound = upper_bound
        self.lower_bound = lower_bound
        super().__init__(symbol, start, end, amount, tc)
        
    def calculate_rsi(self, data):
        delta = data['price'].diff()
        gain = (delta.where(delta > 0, 0)).rolling(window=self.rsi_period).mean()
        loss = (-delta.where(delta < 0, 0)).rolling(window=self.rsi_period).mean()
        rs = gain / loss
        return 100 - (100 / (1 + rs))
        
    def generate_signals(self):
        data = self.data.copy()
        data['RSI'] = self.calculate_rsi(data)
        data['position'] = np.where(data['RSI'] > self.upper_bound, -1,
                                  np.where(data['RSI'] < self.lower_bound, 1, 0))
        self.data = data  # Save for plotting
        return data['position']


# Example usage
if __name__ == "__main__":
    # Example with Moving Average Crossover Strategy
    symbol = "NVDA"
    start = (datetime.now() - timedelta(days=(365*5))).strftime("%Y-%m-%d")
    end = datetime.now().strftime("%Y-%m-%d")
    initial_capital = 100000
    transaction_costs = 0.001
    
    # Initialize and test MA Crossover strategy
    ma_backtest = MovingAverageCrossBacktester(symbol, start, end, 
                                              initial_capital, transaction_costs,
                                              sma1=50, sma2=200)
    
    print("\nTesting Moving Average Crossover Strategy...")
    metrics = ma_backtest.test_strategy()
    
    print("\nStrategy Metrics:")
    for metric, value in metrics.items():
        print(f"{metric}: {value:.4f}")
    
    print("\nPlotting Moving Average Strategy Results...")
    ma_backtest.enhanced_plot_results()
    
    # Optimize strategy parameters
    param_grid = {
        'sma1': (1, 100, 10),
        'sma2': (100, 300, 20)
    }
    
    print("\nOptimizing strategy parameters...")
    optimal_params, optimal_metrics = ma_backtest.optimize_parameters(param_grid)
    
    print("\nOptimal Parameters:", optimal_params)
    print("\nOptimal Strategy Metrics:")
    for metric, value in optimal_metrics.items():
        print(f"{metric}: {value:.4f}")
    
    # Plot enhanced results
    print("\nPlotting Moving Average Strategy Results...")
    ma_backtest.enhanced_plot_results()
    
    # Test RSI Strategy
    print("\nTesting RSI Strategy...")
    rsi_backtest = RSIBacktester(symbol, start, end, initial_capital, 
                                transaction_costs, rsi_period=14,
                                upper_bound=70, lower_bound=30)
    
    rsi_metrics = rsi_backtest.test_strategy()
    
    print("\nRSI Strategy Metrics:")
    for metric, value in rsi_metrics.items():
        print(f"{metric}: {value:.4f}")
    
    # Plot enhanced RSI results
    print("\nPlotting RSI Strategy Results...")
    rsi_backtest.enhanced_plot_results()