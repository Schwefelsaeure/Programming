/*  We will be building a fully functional REST API in under 30 minutes.
 * 
 * You will learn how to
 * - setup a Node.js server with Express
 * - connect that server to MongoDB through Mongoose
 * - setup a REST API with MongoDB and Node.js using Express' middleware feature
 * 
 *  Source: https://www.youtube.com/watch?v=fgTGADljAeg
 */

 // Dependencies
const express = require("express")
const mongoose = require("mongoose")
require("dotenv").config()

// Database setup
mongoose.connect(process.env.DATABASE_URL, { useNewUrlParser: true })
const db = mongoose.connection
db.on("error", (error) => console.error(error))
db.once("open", () => console.log("Connected to database"))

// Application server setup
const app = express()

// Configure the server to accept JSON requests via the "express" middlewere
// and routers/handlers which are defined in subscribers.js
app.use(express.json())
const subscribersRouter = require("./routes/subscribers")
app.use("/subscribers", subscribersRouter)

app.listen(3000, () => console.log("Server started"))