# Software Development Guidelines

## Directory Structure

Firstly, take care of a clean directory structure, e.g.,:

```
- documentation
- resources
- sources
- tests
- README.md
- continous_integration_setup.yaml

```

**Conventions:**
- If a directory contains too much files, split it up in sub-directories.
- Use text files formats instead of binary formats, e.g., use **PlantUML** instead of another UML editor with binary format.


## Development Tools

Then, take care of using up-to-date development tools (keep following list of software up-to-date):

- Version control: Git
- Build tool: language dependent
- Online source code browser and issue tracker: GitLab
- Continuous integration: GitLab
- IDE: Eclipse
- Unit test: language dependent
- Documentation: language dependent and PlantUML and/or draw.io for UML diagrams
- Scipting tasks: use Python
- Office tasks: LibreOffice (including Writer, Calc and Draw) and LaTeX

**Tips:**

- Ship development tools as portable version to developers and modify `PATH` variable temporarily so that developers can easily use the tools. Or, use container software like `Docker` or `vagrant`.
- Do not upgrade software too often to avoid software bugs and incompatibilities!

## Best Practices

- Apply test-driven development (first, think about how to use a module and think about corner cases) and a continuous integration server.
- Document as soon as possible (and document at least purpose and intention of classes).
- Generate UML diagrams with scripts.
- Use issue tracker and assign tickets to you.
- Provide low-level entry for other developers by shipping running examples for your software.
- When programming user interactions (GUI or CLI), always, provide status for user (e.g., task x/n or remaining time) and return correct exit code (for evaluation).
- Hide internal complexities by provide a well-documented and simple external interface (i.e., only a few methods with few, self-explanatory parameters).
- Use a staging branch to consolidate unmature code before merging with master branch.

**Tip**: if running scripts (i.e., cmd1 && cmd2 && ...) consider following strategies:

- Fail immediately: stop and report error to user.
- Fail gracefully: catch errors but execute **ALL** commands and provide a summary of all errors to the user.

- Apply "Infrastructure as Code" paradigm to describe and automate your IT Infrastructure (e.g. `Terraform` for virtual machines and `Ansible` for software on VMs).

## Restructuring Existing Code

- Instead of deleting outdated code immediately,
  * first, add new code (which should replace the outdated code)
  * then, replace the outdated code step by step (by using the new code)

This strategy of baby steps keeps the code functional as long as possible!

E.g. old code is encapsulted in class `OutdatedCalculationTypeA`. Then, add `NewCalculationTypeB` and replace method calls of `OutdatedCalculationTypeA` step by step by `NewCalculationTypeB`.

## Languages

- One language per file to keep it simple!

## Roadmaps

Every software project requires a vision statement and a specific roadmap to inform (potential) users!

Provde following documents:

- Roadmap
- Code architecture (which components exist and how do they interact with each other)
- Development notes (used libraries etc.)
