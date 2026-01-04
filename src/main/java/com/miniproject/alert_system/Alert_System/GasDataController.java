package com.miniproject.alert_system.Alert_System;

import org.springframework.web.bind.annotation.*;

import java.util.List;
import java.util.Map;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.ResponseEntity;

@RestController
@RequestMapping("/api")
public class GasDataController {

    @Autowired
    private GasDataRepository gasDataRepository;

    @CrossOrigin(origins = "*")
    @GetMapping("/server-status")
    public String serverStatus(){
        System.out.println("Server status request..");
        return "Server is Runningj";
    }

    @CrossOrigin(origins = "*")
    @PostMapping("/upload-gas-data")
    public ResponseEntity<?> receiveGasData(@RequestBody Map<String, Integer> payload) {
        System.out.println("Uploading the gas data");
        if (!payload.containsKey("gas_level")) {
            return ResponseEntity.badRequest().body("Missing 'gas_level' in request.");
        }

        int gasLevel = payload.get("gas_level");
        System.out.println("Gas Level:" + gasLevel);
        // Save the gas data to the database
        GasData gasData = new GasData(gasLevel);
        gasDataRepository.save(gasData);

        // Return success response
        return ResponseEntity.ok(Map.of(
                "message", "Gas data received successfully.",
                "gas_level", gasLevel,
                "status", gasLevel > 400 ? "CRITICAL" : "NORMAL"
        ));
    }

    // Optional: Get all records
    @CrossOrigin(origins = "*")
    @GetMapping("/gas-data")
    public ResponseEntity<?> getAllGasData() {
        System.out.println("Getting all the gas data");
        return ResponseEntity.ok(gasDataRepository.findAll());
    }

    @CrossOrigin(origins = "*")
    @GetMapping("/gas-data/latest")
    public List<GasData> getLatestGasData() {   
        return gasDataRepository.findLatest100();
    }
}
