// server.js
const express = require("express");
const mongoose = require("mongoose");
const cors = require("cors");

const app = express();
const PORT = 4000;

// Middleware
app.use(cors());
app.use(express.json());

// MongoDB connection
mongoose
  .connect("mongodb://localhost:27017/bookstore", {
    useNewUrlParser: true,
    useUnifiedTopology: true,
  })
  .then(() => console.log("MongoDB connected"))
  .catch((err) => console.error("MongoDB error:", err));

// Schemas & Models
const userSchema = new mongoose.Schema({
  name: String,
  email: String,
  password: String, // NOTE: plain text for demo only
});

const bookSchema = new mongoose.Schema({
  title: String,
  author: String,
  price: Number,
});

const User = mongoose.model("User", userSchema);
const Book = mongoose.model("Book", bookSchema);

// Seed some books if empty
async function seedBooks() {
  const count = await Book.countDocuments();
  if (count === 0) {
    await Book.insertMany([
      { title: "Clean Code", author: "Robert C. Martin", price: 450 },
      { title: "Introduction to Algorithms", author: "Cormen", price: 900 },
      { title: "JavaScript: The Good Parts", author: "Douglas Crockford", price: 350 },
      { title: "Operating System Concepts", author: "Silberschatz", price: 700 },
    ]);
    console.log("Sample books inserted");
  }
}
seedBooks();

// Routes
app.get("/", (req, res) => {
  res.send("Online Book Store API running");
});

// Registration
app.post("/api/register", async (req, res) => {
  try {
    const { name, email, password } = req.body;
    const existing = await User.findOne({ email });
    if (existing) {
      return res.status(400).json({ message: "User already exists" });
    }
    const user = new User({ name, email, password });
    await user.save();
    res.json({ message: "Registration successful", userId: user._id });
  } catch (err) {
    console.error(err);
    res.status(500).json({ message: "Server error" });
  }
});

// Login
app.post("/api/login", async (req, res) => {
  try {
    const { email, password } = req.body;
    const user = await User.findOne({ email, password });
    if (!user) {
      return res.status(401).json({ message: "Invalid credentials" });
    }
    res.json({ message: "Login successful", name: user.name });
  } catch (err) {
    console.error(err);
    res.status(500).json({ message: "Server error" });
  }
});

// Catalogue: list of books
app.get("/api/books", async (req, res) => {
  try {
    const books = await Book.find();
    res.json(books);
  } catch (err) {
    console.error(err);
    res.status(500).json({ message: "Server error" });
  }
});

app.listen(PORT, () => {
  console.log(`Server running on http://localhost:${PORT}`);
});
