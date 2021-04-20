const { TestScheduler } = require("jest")
const LinkedList = require("./LinkedList")

describe("#insertAtHead", () => {
    test("adds element at the beginning of the list", () => {
        const linkedList = new LinkedList()
        expect(linkedList.head).toBe(null)

        expectedHeadValue = 1
        linkedList.insertAtHead(expectedHeadValue)

        expect(linkedList.head.value).toBe(expectedHeadValue)
        expect(linkedList.length).toBe(1)
    })
})

describe("#insertAt", () => {
    
    test("returns null upon negative indices", () => {
        const linkedList = LinkedList.fromValues(1, 2)
        expect(linkedList.insertAt(-1)).toBeNull()
        expect(linkedList.length).toBe(2)
    })

    test("returns null upon too large indices", () => {
        const linkedList = LinkedList.fromValues(1, 2)
        expect(linkedList.insertAt(3)).toBeNull()
        expect(linkedList.length).toBe(2)
    })

    test("returns head if index == 0", () => {
        const linkedList = LinkedList.fromValues(1, 2)
        expect(linkedList.insertAt(0, 10).value).toBe(10)
        expect(linkedList.length).toBe(3)
    })

    test("returns node if index < length of list", () => {
        const linkedList = LinkedList.fromValues(1, 2)
        expect(linkedList.insertAt(1, 10).value).toBe(10)
        expect(linkedList.length).toBe(3)
    })

    test("returns node if index points to last element", () => {
        const linkedList = LinkedList.fromValues(1, 2)
        expect(linkedList.insertAt(2, 10).value).toBe(10)
        expect(linkedList.length).toBe(3)
    })

})

describe("#getByIndex", () => {

    describe("with index less than 0", () => {
        test("it returns null", () => {
            const linkedList = LinkedList.fromValues(1, 2)

            expect(linkedList.getByIndex(-1)).toBeNull()
        })
    })

    describe("with index greater than list length", () => {
        test("it returns null", () => {
            const linkedList = LinkedList.fromValues(1, 2)

            expect(linkedList.getByIndex(3)).toBeNull()
        })
    })

    describe("with index 0", () => {
        test("it returns the head element", () => {
            const linkedList = LinkedList.fromValues(1, 2)

            expect(linkedList.getByIndex(0).value).toBe(1)
        })
    })

    describe("with index in the middle", () => {
        test("it returns that element", () => {
            const linkedList = LinkedList.fromValues(1, 2, 3, 4)

            expect(linkedList.getByIndex(2).value).toBe(3)
        })
    })

    describe("with index at end it returns the last element", () => {
        test("it returns that element", () => {
            const linkedList = LinkedList.fromValues(1, 2, 3, 4)

            expect(linkedList.getByIndex(3).value).toBe(4)
        })
    })

})

describe("#removeAtIndex", () => {
    
    test("does nothing upon negative indices", () => {
        const linkedList = LinkedList.fromValues(1, 2, 3)

        linkedList.removeAtIndex(-1)

        expect(linkedList.length).toBe(3)
        expect(linkedList.getByIndex(0).value).toBe(1)
        expect(linkedList.getByIndex(2).value).toBe(3)
    })

    test("does nothing upon too large indices", () => {
        const linkedList = LinkedList.fromValues(1, 2, 3)

        linkedList.removeAtIndex(3)

        expect(linkedList.length).toBe(3)
        expect(linkedList.getByIndex(0).value).toBe(1)
        expect(linkedList.getByIndex(2).value).toBe(3)
    })

    test("removes head if index == 0", () => {
        const linkedList = LinkedList.fromValues(1, 2, 3)

        linkedList.removeAtIndex(0)

        expect(linkedList.length).toBe(2)
        expect(linkedList.getByIndex(0).value).toBe(2)
        expect(linkedList.getByIndex(1).value).toBe(3)
    })

    test("returns node if index < length of list", () => {
        const linkedList = LinkedList.fromValues(1, 2, 3)

        linkedList.removeAtIndex(1)

        expect(linkedList.length).toBe(2)
        expect(linkedList.getByIndex(0).value).toBe(1)
        expect(linkedList.getByIndex(1).value).toBe(3)
    })

})