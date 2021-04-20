// Tip: Use extension "REST Client" 

// Dependencies
const express = require("express")
const router = express.Router()
const Subscriber = require("../models/subscriber")

// Getting all
router.get("/", async (req, res) => {
    try {
        const subscribers = await Subscriber.find()
        res.json(subscribers)
    } catch(error) {
        res.status(500).json({message: error.message})
    }
})

// Getting one
router.get("/:id", getSubscriberById, (req, res) => {
    // req.params.id returns ":id"
    res.json(res.subscriber)
})

// Creating one
router.post("/", async (req, res) => {
    // req.params.id returns ":id"
    const subsriber = new Subscriber({
        name: req.body.name,
        subscribeToChannel: req.body.subscribeToChannel
    })

    try {
        const newSubscriber = await subsriber.save()
        res.status(201).json(newSubscriber)
    } catch(error) {
        res.status(400).json({message: error.message})
    }
})

// Updating one
router.patch("/:id", getSubscriberById, async (req, res) => {
    if (req.body.name != null) {
        res.subscriber.name = req.body.name
    }

    if (req.body.subscribeToChannel != null) {
        res.subscriber.subscribeToChannel = req.body.subscribeToChannel
    }

    try {
        const updatedSubscriber = await res.subscriber.save()
        res.json(updatedSubscriber)
    } catch (error) {
        res.status(400).json({message: error.message})
    }
})

// Deleting one
router.delete("/:id", getSubscriberById, async (req, res) => {
    try {
        await res.subscriber.remove()
        res.json({message: "Deleted subscriber" })
    } catch (error) {
        res.status(500).json({message: error.message})
    }
})

// A helper function which processes a given subscriber id
async function getSubscriberById(req, res, next) {
    let subscriber

    try {
        subscriber = await Subscriber.findById(req.params.id)

        if (subscriber == null) {
            return res.status(404).json({message: "Cannot find subscriber"})
        }
    } catch(error) {
        return res.status(500).json({message: error.message})
    }

    res.subscriber = subscriber
    next()
}

module.exports = router