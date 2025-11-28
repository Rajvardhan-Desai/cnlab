VIT Semester Result - Minimal Full Stack Project
=================================================

Requirements on a NEW machine:
- Java 17+
- Maven
- MongoDB running on localhost:27017
- Any modern web browser (Chrome, Edge, Firefox...)

Steps:

1) Start MongoDB
   - Ensure MongoDB is running at mongodb://localhost:27017
   - Default database used: vit_results

2) Start Spring Boot backend
   - Open terminal
   - cd backend
   - mvn spring-boot:run

   Backend will start on: http://localhost:8080
   API: POST /api/results , GET /api/results

3) Open frontend
   - Open frontend/index.html in your browser (double-click or via "Open File")
   - Fill student details + marks
   - Click "Save & Calculate"

   The page will call http://localhost:8080/api/results
   and display per-subject totals (30% MSE + 70% ESE) and overall percentage.

No npm / node / create-react-app needed.
React is loaded from CDN and runs directly in the browser.
