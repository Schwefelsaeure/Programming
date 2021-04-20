/* The "Calculator" class allows to combine two numbers by one mathematical
 * operation and updates the "output" HTML element.
 *
 * The class stores the current and previous operand and the mathematical
 * operator into state variables while typing and carries out the computation
 * when the "=" button is clicked.
 * 
 * Idea from: https://www.youtube.com/watch?v=j59qQ7YWLxw
 */
class Calculator {
    constructor(previousOperandTextElement, currentOperandTextElement) {
        this.previousOperandTextElement = previousOperandTextElement
        this.currentOperandTextElement = currentOperandTextElement
        this.clear()
    }

    clear() {
        this.previousOperand = ""
        this.currentOperand = ""
        this.operation = undefined
    }

    delete() {
        this.currentOperand = this.currentOperand.toString().slice(0, -1)
    }

    appendNumber(number) {
        if (number === "." && this.currentOperand.includes(".")) {
            return
        }

        this.currentOperand = this.currentOperand.toString() + number.toString()
    }

    chooseOperation(operation) {
        if (this.currentOperand === "") {
            return
        }
        if (this.previousOperand !== "") {
            this.compute()
        }

        this.operation = operation
        this.previousOperand = this.currentOperand
        this.currentOperand = ""
    }

    compute() {
        const previousOperand = parseFloat(this.previousOperand)
        const currentOperand = parseFloat(this.currentOperand)
        let computation

        if (isNaN(previousOperand) || isNaN(currentOperand)) {
            return
        }

        switch(this.operation) {
            case "/":
                computation = previousOperand / currentOperand
                break
            case "*":
                computation = previousOperand * currentOperand
                break
            case "+":
                computation = previousOperand + currentOperand
                break
            case "-":
                computation = previousOperand - currentOperand
                break
            default:
                console.log("Invalid operation: " + this.operation)
                return
        }

        this.currentOperand = computation
        this.previousOperand = ""
        this.operation = undefined
    }

    updateDisplay() {
        this.currentOperandTextElement.innerText = this.formatNumber(this.currentOperand)

        if (this.operation != null) {
            this.previousOperandTextElement.innerText = 
            `${this.formatNumber(this.previousOperand)} ${this.operation}`
        }
        else {
            this.previousOperandTextElement.innerText = this.formatNumber(this.previousOperand)
        }
    }

    formatNumber(number) {
        const stringNumber = number.toString()
        const integerPart = parseFloat(stringNumber.split(".")[0])
        const decimalPart = stringNumber.split(".")[1]

        let integerFormatted = (isNaN(integerPart)) ? "" : integerPart.toLocaleString("en", { maximumFractionDigits: 0 }) ;
        
        if (decimalPart != null) {
            return `${integerFormatted}.${decimalPart}`
        } else {
            return integerFormatted
        }
    }
}

/* Bind HTML elements to JavaScript objects to be able to update them */
const numberButtons = document.querySelectorAll("[data-number]")
const operationButtons = document.querySelectorAll("[data-operation]")

const equalsButton = document.querySelector("[data-equal]")
const deleteButton = document.querySelector("[data-delete]")
const allClearButton = document.querySelector("[data-all-clear]")

const previousOperandTextElement = document.querySelector("[data-previous]")
const currentOperandTextElement = document.querySelector("[data-current]")

/* Connect GUI elements and "Calculator" class by using event handlers */
const calculator = new Calculator(previousOperandTextElement, currentOperandTextElement)

numberButtons.forEach(button => {
    button.addEventListener("click", () => {
        calculator.appendNumber(button.innerText)
        calculator.updateDisplay()
    })
})

operationButtons.forEach(button => {
    button.addEventListener("click", () => {
        calculator.chooseOperation(button.innerText)
        calculator.updateDisplay()
    })
})

equalsButton.addEventListener("click", button => {
    calculator.compute()
    calculator.updateDisplay()
})

allClearButton.addEventListener("click", button => {
    calculator.clear()
    calculator.updateDisplay()
})

deleteButton.addEventListener("click", button => {
    calculator.delete()
    calculator.updateDisplay()
})