// The webserver
const express = require("express")
const app = express()
const port = 3000

// The socket communication
const server = require("http").Server(app)
const io = require("socket.io")(server)

const { v4: uuidV4 } = require("uuid")

app.set("view engine", "ejs")
app.use(express.static("public"))

// Set up routes on the page

// Direct user to a new room
app.get("/", (req, res) => {
    res.redirect(`/${uuidV4()}`)
})

// Render room and provide parameters for template engine "ejs"
app.get("/:room", (req, res) => {
    res.render("room", { roomId: req.params.room })
})

// After a user connected to a room, use socket.io in the frontend so that participants communicate directly with each other
io.on("connection", socket => {
    socket.on("join-room", (roomId, userId) => {
        socket.join(roomId)

        socket.to(roomId).emit("user-connected", userId)
        
        socket.on("disconnect", () => {
            socket.to(roomId).emit("user-disconnected", userId)
        })
    })
})

server.listen(port)