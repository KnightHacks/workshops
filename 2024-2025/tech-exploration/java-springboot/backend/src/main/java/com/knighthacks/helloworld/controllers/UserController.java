package com.knighthacks.helloworld.controllers;

import org.springframework.web.bind.annotation.RestController;

import com.knighthacks.helloworld.entity.User;
import com.knighthacks.helloworld.repository.UserRepository;

import java.util.List;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;


@RestController
public class UserController {

  @Autowired
  private UserRepository userRepository;

  @GetMapping("/v1/users")
  public ResponseEntity<List<User>> getMethodName() {
    return ResponseEntity.ok(userRepository.findAll());
  }

  @PostMapping("/v1/login-signup")
  public ResponseEntity<User> postMethodName(@RequestBody User user) {
      try{
        User existingUser = userRepository.findByName(user.getName());
        if (existingUser != null){
          return new ResponseEntity<>(existingUser, HttpStatus.OK);
        }
        userRepository.save(user);
        return new ResponseEntity<>(user, HttpStatus.CREATED);
      }
      catch (Exception e) {
        return new ResponseEntity<>(null, HttpStatus.INTERNAL_SERVER_ERROR);
    }
  }

  @GetMapping("/v1/leaders")
  public ResponseEntity<List<Object[]>> getLeaderList() {
    return ResponseEntity.ok(userRepository.findUsersWithBestScoreNative());
  }
}
