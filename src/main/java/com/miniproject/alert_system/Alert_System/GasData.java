package com.miniproject.alert_system.Alert_System;


import jakarta.persistence.*;
import java.time.LocalDateTime;

@Entity
@Table(name = "gas_data")
public class GasData {

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;

    @Column(name = "gas_level", nullable = false)
    private int gasLevel;

    @Column(name = "timestamp", nullable = false)
    private LocalDateTime timestamp = LocalDateTime.now();

    // Constructors
    public GasData() {}

    public GasData(int gasLevel) {
        this.gasLevel = gasLevel;
        this.timestamp = LocalDateTime.now();
    }

    // Getters and setters
    public Long getId() {
        return id;
    }

    public int getGasLevel() {
        return gasLevel;
    }

    public void setGasLevel(int gasLevel) {
        this.gasLevel = gasLevel;
    }

    public LocalDateTime getTimestamp() {
        return timestamp;
    }

    public void setTimestamp(LocalDateTime timestamp) {
        this.timestamp = timestamp;
    }
}

