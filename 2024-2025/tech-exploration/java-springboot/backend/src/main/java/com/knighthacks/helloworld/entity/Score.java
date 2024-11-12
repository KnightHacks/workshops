package com.knighthacks.helloworld.entity;

import jakarta.persistence.CascadeType;
import jakarta.persistence.Entity;
import jakarta.persistence.FetchType;
import jakarta.persistence.GeneratedValue;
import jakarta.persistence.GenerationType;
import jakarta.persistence.Id;
import jakarta.persistence.ManyToOne;
import jakarta.persistence.SequenceGenerator;

@Entity
public class Score {
  @Id
  @SequenceGenerator( name ="score_id_sequence", sequenceName = "score_id_sequence")
  @GeneratedValue( strategy = GenerationType.SEQUENCE, generator = "score_id_sequence")
  private Integer id;
  private Integer score;

  @ManyToOne(fetch = FetchType.EAGER, cascade=CascadeType.MERGE)
  private User user;

  public Score(){ }
  public Score(Integer id, User user){
    this.id = id;
    this.user = user;
  }

  public Integer getId() {
    return id;
  }

  public void setId(Integer id){
    this.id = id;
  }

  public Integer getScore(){
    return score;
  }

  public void setScore(Integer score){
    this.score = score;
  }

  public User getUser() {
    return user;
  }

  public void setUser(User user){
    this.user = user;
  }
}
