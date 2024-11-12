package com.knighthacks.helloworld.repository;

import java.util.List;

import org.springframework.data.domain.Sort;
import org.springframework.data.jpa.repository.JpaRepository;

import com.knighthacks.helloworld.entity.Score;

public interface ScoreRepository extends JpaRepository<Score, Integer> {
  List<Score> findAllByUserId(Integer userId, Sort sort);
}
