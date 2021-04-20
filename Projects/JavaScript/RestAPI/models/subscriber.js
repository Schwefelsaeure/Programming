const mongoose = require("mongoose")

// Create a database schema to interact with the database easily
const subscriberSchema = new mongoose.Schema({
    name: {
        type: String,
        required: true
    },
    subscribeToChannel: {
        type: String,
        required: true
    },
    subscribeDate: {
        type: Date,
        required: true,
        default: Date.now
    }
})

// The model function provides an object-relational mapper to the database
module.exports = mongoose.model("Subscriber", subscriberSchema)