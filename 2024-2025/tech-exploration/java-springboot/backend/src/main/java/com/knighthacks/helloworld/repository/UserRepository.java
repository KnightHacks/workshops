package com.knighthacks.helloworld.repository;

import java.util.List;

import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Query;
import org.springframework.stereotype.Repository;

import com.knighthacks.helloworld.entity.User;

@Repository
public interface UserRepository extends JpaRepository<User, Integer> {

  @Query(value = "SELECT u.id AS userId, u.name AS userName, COALESCE(MAX(s.score), 0) AS bestScore " +
               "FROM demoentity u " +
               "LEFT JOIN score s ON u.id = s.user_id " +
               "GROUP BY u.id " +
               "ORDER BY bestScore DESC", nativeQuery = true)
  List<Object[]> findUsersWithBestScoreNative();

  User findByName(String name);

}
