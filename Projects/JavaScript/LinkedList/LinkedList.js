class LinkedList {
    constructor() {
        this.head = null
        this.length = 0
    }

    insertAtHead(data) {
        const newNode = new LinkedListNode(data, this.head)
        this.head = newNode
        this.length++

        return newNode
    }

    insertAt(index, data) {
        if (index == 0) {
            return this.insertAtHead(data)
        } else {
            let previousNode = this.getByIndex(index - 1)

            if (previousNode == null) {
                return null
            } else {
                previousNode.next = new LinkedListNode(data, previousNode.next)
                this.length++
                return previousNode.next
            }
        }
    }

    getByIndex(index) {
        if (index < 0 || index >= this.length) {
            return null
        } else {
            let currentElement = this.head
            for (let i = 0; i < index; i++) {
                currentElement = currentElement.next
            }
            return currentElement
        }
    }

    removeAtHead() {
        if (this.head != null) {
            this.head = this.head.next
            this.length--
        }
    }

    removeAtIndex(index) {
        if (index == 0) {
            this.removeAtHead()
        } else {
            let predecessor = this.getByIndex(index - 1)
            let current = this.getByIndex(index)

            if (predecessor != null && current != null) {
                predecessor.next = current.next
                this.length--
            }
        }
    }

    print() {
        let output = ""

        let currentElement = this.head
        while (currentElement) {
            output = `${output}${currentElement.value} -> `
            currentElement = currentElement.next
        }

        console.log(`${output}null`)
    }
}

class LinkedListNode {
    constructor(value, next) {
        this.value = value
        this.next = next
    }
}

LinkedList.fromValues = function(...values) {
    const linkedList = new LinkedList()

    for (let i = values.length - 1; i >= 0; i--) {
        linkedList.insertAtHead(values[i])
    }

    return linkedList
}

module.exports = LinkedList