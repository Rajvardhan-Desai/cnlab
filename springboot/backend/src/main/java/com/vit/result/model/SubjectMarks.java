package com.vit.result.model;

public class SubjectMarks {
    private String name;
    private double mse;
    private double ese;
    private double total;

    public SubjectMarks() {}

    public String getName() { return name; }
    public void setName(String name) { this.name = name; }

    public double getMse() { return mse; }
    public void setMse(double mse) { this.mse = mse; }

    public double getEse() { return ese; }
    public void setEse(double ese) { this.ese = ese; }

    public double getTotal() { return total; }
    public void setTotal(double total) { this.total = total; }
}
