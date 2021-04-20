# Writing Commit Messages

- First, summarize changes in one sentence (with around 80 characters).
- Then, list important changes in files. For instance:

  ```
  path/to/file/x.txt
  - Add foo.
  
  path/to/file/y.txt
  - Add bar.
  ```

**Note:** Use present tense for commit messages (the default for Git)

## Notes

- Separate summary and list of important changes with a newline.
- Optional: use smart commit feature of version control system. For instance, to close a corresponding issue.

Example of complete commit message:

```
In "Foo", add xyz feature.

path/to/file/x.txt
- Add foo.
  
path/to/file/y.txt
- Add bar.


Issue-34 #close In "Foo", add xyz feature.
```

Watch out: Before publishing (pushing) anything, pull all remote changes in your branch.

## Commiting Binaries

- Don't commit large binary files (> 5 MiB)! Use cloud space for such artifacts and automated the process to transfer these files to the cloud space.
