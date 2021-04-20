# MVC Pattern

- MVC = Model View Controller
- Goal: separate concerns


## Overview

```
        +-------+
        | Model |
        +-------+
updates |       ^ changes      
        v       | 
 +------+       +------------+
 | View |       | Controller |
 +------+       +------------+
        |       ^
   sees v       | triggers
        +-------+
        | User  |
        +-------+
```

Description in prose:

- `User` triggers `Controller` to change `Model`.
- `Controller` changes `Model`.
- `Model` updates `View`.
  * Either `Model` pushes new information to `View`.
  * Or `View` pulls new information from `Model`
  * Usually, implemented as observer pattern.
  * I.e., `Model` holds a list of observers and calls an `update()` method upon changes which is implemented by (different) `Views`.

## Example

A simple example to visualize and update student information.

```
@startuml

' Classes
class StudentController {
    -Student model
    -StudentConsoleView view
    --
    +StudentController()
    --
    +void setStudentName()
    +String getStudentName()
    +void setStudentRollNo()
    +String getStudentRollNo()
    --
    +void updateView()
}

class Student {
    -String name
    -String rollNo
    --
    +String getName()
    +void setName()
    +String getRollNo()
    +void setRollNo()
}

class StudentConsoleView {
    +void printStudentDetails()
}

class Main {
    +void main()
}

' Assocations
Main -> StudentController : instantiate MVC objects
StudentController -> Student : changes 
StudentController -> : StudentConsoleView : updates

@enduml
```

## Important Remarks

- The `Controller` encapsulates `Model` and `View` and duplicates their methods.
- The `View` gets information directly from `Model` via push or pull mechanism.
- A new `View` implementation requires a new `View` and also a new `Controller`.

## Coding Tips

- Use following structure for GUI classes:
  * All GUI elements are member variables.
  * Implement three methods which are called in constructor: `createGuiElements()`, `groupGuiElements()` and `placeGuiElements()`.
  * Note: The last two methods set the layout of (helper) panels and not `createGuiElements()`. I.e., the developer directly sees the applied layout when placing GUI elements.
