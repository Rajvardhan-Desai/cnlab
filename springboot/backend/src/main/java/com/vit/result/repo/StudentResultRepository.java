package com.vit.result.repo;

import com.vit.result.model.StudentResult;
import org.springframework.data.mongodb.repository.MongoRepository;

public interface StudentResultRepository extends MongoRepository<StudentResult, String> {
}
