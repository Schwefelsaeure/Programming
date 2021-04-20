# UML Tools

- PlantUML: https://plantuml.com/ (textual description of UML diagrams)
- draw.io: https://www.diagrams.net/ (powerful diagraming tool)

**Tip:** For each source file `file.source` store UML diagram type in a distinct file annotated with its suffix. E.g., store a class diagram in `file.source.class.iodraw` and a package diagram in `file.source.package.iodraw`.

Watch out: Keep diagrams as simple as possible to promote understanding!

## Workflow PlantUML

```
@startuml(id=myid)
...
@enduml
```

## Workflow draw.io

1. First, create all actions and conditions (according to source code).
2. Then, connect all elements with connectors and label all(!) connectors.
3. Layout elements: Select all elements (group elements if necessary), distribute horizontally and center.
4. Style elements (e.g. activate shadows for all vertices: `Edit -> Select Vertices -> Checkbox "Shadow"`).

### Tips

- For activity diagrams, use "BPMN General -> Conversation" as decision shape (**with slope angle 0.05**) instead of the classic rhombus shape because this polygon handles long texts better than the rhombus.
