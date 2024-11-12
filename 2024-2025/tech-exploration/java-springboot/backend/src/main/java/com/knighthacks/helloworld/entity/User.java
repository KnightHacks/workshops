package com.knighthacks.helloworld.entity;

import jakarta.persistence.Column;
import jakarta.persistence.Entity;
import jakarta.persistence.GeneratedValue;
import jakarta.persistence.GenerationType;
import jakarta.persistence.Id;
import jakarta.persistence.SequenceGenerator;
import jakarta.persistence.Table;

@Entity
@Table(name = "demoentity")
public class User {
	
	@Id
  @SequenceGenerator( name ="demo_id_sequence", sequenceName = "demo_id_sequence")
  @GeneratedValue( strategy = GenerationType.SEQUENCE, generator = "demo_id_sequence")
	private Integer id;
  @Column(unique = true)
	private String name;
	
	public User() {
	}
	
	public User(String name) {
		this.name = name;
	}
	public Integer getId() {
		return id;
	}
	public void setId(Integer id) {
		this.id = id;
	}
	public String getName() {
		return name;
	}
	public void setName(String name) {
		this.name = name;
	}
	
}
