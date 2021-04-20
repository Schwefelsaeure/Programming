const socket = io("/")
// The "peer" module is used as convience wrapper for the WebRTC communication
// and for generating user ids.
// After having user ids, we can call different users with this ids.
const myPeer = new Peer(undefined, {
    host: "/",
    port: "3001"
})

const videoGrid = document.getElementById("video-grid")
const connectedPeers = {}

navigator.mediaDevices.getUserMedia({
    video: true,
    audio: true
}).then(stream => {
    renderOwnVideoOnGrid(stream)
    renderOtherVideosOnGrid(stream)

    // Send video stream to newly connected users
    socket.on("user-connected", userId => {
        makeWebRtcCall(userId, stream)
    })
}).catch((error) => {
    alert(error)
})

function renderOwnVideoOnGrid(stream) {
    const myVideo = document.createElement("video")
    myVideo.muted = true
    addStreamToVideoGrid(myVideo, stream)
}

function addStreamToVideoGrid(video, stream) {
    video.srcObject = stream
    video.addEventListener("loadedmetadata", () => {
        video.play()
    })
    videoGrid.append(video)
}

function renderOtherVideosOnGrid(stream) {
    myPeer.on("call", call => {
        call.answer(stream)

        const otherVideo = document.createElement("video")
        call.on("stream", userVideoStream => {
            addStreamToVideoGrid(otherVideo, userVideoStream)
        })
    })
}

function makeWebRtcCall(userId, stream) {
    const call = myPeer.call(userId, stream)
    const otherVideo = document.createElement("video")

    call.on("stream", otherStream => {
        addStreamToVideoGrid(otherVideo, otherStream)
    })

    call.on("close", () => {
        otherVideo.remove()
    })

    connectedPeers[userId] = call
}

myPeer.on("open", id => {
    socket.emit("join-room", ROOM_ID, id)
})

socket.on("user-disconnected", userId => {
    console.log(userId)
    if (connectedPeers[userId]) {
        connectedPeers[userId].close()
    }
})