package com.vit.result.model;

import org.springframework.data.annotation.Id;
import org.springframework.data.mongodb.core.mapping.Document;

@Document(collection = "student_results")
public class StudentResult {
    @Id
    private String id;
    private String regNo;
    private String name;
    private java.util.List<SubjectMarks> subjects;
    private double overallPercentage;

    public String getId() { return id; }
    public void setId(String id) { this.id = id; }

    public String getRegNo() { return regNo; }
    public void setRegNo(String regNo) { this.regNo = regNo; }

    public String getName() { return name; }
    public void setName(String name) { this.name = name; }

    public java.util.List<SubjectMarks> getSubjects() { return subjects; }
    public void setSubjects(java.util.List<SubjectMarks> subjects) { this.subjects = subjects; }

    public double getOverallPercentage() { return overallPercentage; }
    public void setOverallPercentage(double overallPercentage) { this.overallPercentage = overallPercentage; }
}
