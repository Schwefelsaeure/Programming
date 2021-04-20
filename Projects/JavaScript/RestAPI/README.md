# README

A simple REST API which accepts JSON requests and reads and writes them to a NoSQL database (Mongo)

## Getting Started

1. Install MongoDB (https://docs.mongodb.com/manual/tutorial/install-mongodb-on-ubuntu/)
2. `sudo systemctl start mongod`
3. `npm install`
4. `npm run devStart`

## Source Code Structure

- `server.js`: This is the entry point of the application which uses the Node.js module `express` to start a webserver.
- `routes/subscribers.js`: This represents the middleware functions which handle the actual REST API requests (GET, POST, PATCH etc.).
- `models/subscriber.js`: This represents an object-relational mapper to write into the Mongo database.
