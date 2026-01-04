package com.miniproject.alert_system.Alert_System;

import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Query;

import java.util.List;

public interface GasDataRepository extends JpaRepository<GasData, Long> {
    // You can add custom queries here if needed
    @Query(value = "SELECT * FROM gas_data ORDER BY timestamp DESC LIMIT 100", nativeQuery = true)
    List<GasData> findLatest100();
}
