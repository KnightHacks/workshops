package com.knighthacks.helloworld.controllers;

import java.util.List;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.data.domain.Sort;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.RestController;

import com.knighthacks.helloworld.entity.Score;
import com.knighthacks.helloworld.repository.ScoreRepository;

import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;

@RestController
public class ScoreController {

  @Autowired
  public ScoreRepository scoreRepository;

  @GetMapping("/v1/score")
  public ResponseEntity<List<Score>> getScores() {
    return ResponseEntity.ok(scoreRepository.findAll());
  }

  @GetMapping("/v1/score/{userId}")
  public ResponseEntity<List<Score>> getScoreByUserId(@PathVariable("userId") Integer userId) {
    return ResponseEntity.ok(scoreRepository.findAllByUserId(userId, Sort.by(Sort.Order.desc("id"))));
  }

  @PostMapping("/v1/score")
  public ResponseEntity<Score> addScore(@RequestBody Score score){
    scoreRepository.save(score);
    return ResponseEntity.ok(score);
  }
}
