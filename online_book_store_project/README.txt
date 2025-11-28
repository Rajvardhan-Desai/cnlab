Online Book Store - React + Node.js + MongoDB
===============================================

This is a minimal full-stack demo for an online book store with:
1) Home Page
2) Login Page
3) Catalogue Page
4) Registration Page (stored in MongoDB)

Requirements:
- Node.js installed
- MongoDB running on mongodb://localhost:27017
- Any modern web browser

Backend setup:
--------------
1. Open a terminal and go to the backend folder:
   cd backend

2. Install dependencies:
   npm install

3. Start the server:
   npm start

   The API will run at: http://localhost:4000
   Endpoints:
   - GET  /api/books
   - POST /api/register
   - POST /api/login

Frontend setup:
---------------
1. Open the frontend/index.html file in your browser (double-click or "Open File").
2. Use the navbar to navigate:
   - Home
   - Catalogue (loads books from backend)
   - Login (calls /api/login)
   - Register (calls /api/register and stores in MongoDB)
