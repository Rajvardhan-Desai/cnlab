package com.vit.result.controller;

import com.vit.result.model.StudentResult;
import com.vit.result.model.SubjectMarks;
import com.vit.result.repo.StudentResultRepository;
import org.springframework.web.bind.annotation.*;

@RestController
@CrossOrigin(origins = "*") // allow frontend from any origin
@RequestMapping("/api/results")
public class ResultController {

    private final StudentResultRepository repo;

    public ResultController(StudentResultRepository repo) {
        this.repo = repo;
    }

    @PostMapping
    public StudentResult create(@RequestBody StudentResult sr) {
        double sum = 0.0;
        java.util.List<SubjectMarks> subs = sr.getSubjects();
        if (subs != null && !subs.isEmpty()) {
            for (SubjectMarks sm : subs) {
                double total = 0.3 * sm.getMse() + 0.7 * sm.getEse();
                sm.setTotal(total);
                sum += total;
            }
            sr.setOverallPercentage(sum / subs.size());
        }
        return repo.save(sr);
    }

    @GetMapping
    public java.util.List<StudentResult> getAll() {
        return repo.findAll();
    }
}
