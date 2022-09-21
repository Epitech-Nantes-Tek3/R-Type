## Development Rules

The rules to contribute to the R-Type project are write down below.


### Committing Rules

First, the commits. They should always look like the following description:

Action Verb (Add, Delete, Fix ...) + Title + Description of what you have done + Related Issue Number

This should look like this:

```bash
    git commit -m "Add new rules to the CONTRIBUTING.md

    Add Committing Rules #2"
```

You should always commit frequently and based on the given exemple.

If possible, please certify your commits (-S).


### Branch Rules

The branch name should consider the issue title and the issue number in its name

Example:

```bash
    git checkout -b 2-Documentation-Create-The-Contributing.md
```

You must make one branch per issue.

Try to push as regularly as possible so everyone can see where you are at.
When first committing on a branch, open a draft, so it will be easier for your mates to see where you are at.


### Pull Request Rules

When your work is done on a branch, you must make a pull request.

The name is the same for the branch.
However, you must write a description as a reminder of what you have done.
It may be all about the issue, but often you have unexpected fixes.

For the reviewers, prioritize the people who can really help you with your work.

You must have at least 2 reviewers who approve your pull request.

Try not to exceed 24 hours before reading your PRs.

It is obviously forbidden to approve a merge until all the reviewers have accepted the PR as well as the success of the workflows.


### Issue Rules

When creating an issue, you must follow the given format :

* The name of the issue must correspond to the part of the code concerned

```bash
    Name : Documentation - Create the Contributing.md
```

* Describing the issue is mandatory. Try to be concise with the features who will be added on the project.

* Add a label to clarify the issue. If there is no label existing or corresponding to your issue, create one and describe it.

* Take a moment to put the issue in the project, if it hasn't been done automatically.


### Testing Rules

When something can be verified by a test, we will be looking for tests in your PR.

The lack of test in your code can be one of the reasons of refusing a PR.


### Documentation Rules

We using Doxygen for documentation, and in order to allow the proper deployment of the documentation, please respect the following protocol:

* Please add the \file at the top of each of your files :

```bash
    /// @file path/from/the/repository/root.hpp
```

* Please document your defines and typedefs as follows :

```bash
    ///
    /// @brief I am a basic function
    ///
```

* Please document your functions in the header as follows:

```bash
    ///
    /// @brief Print a string
    ///
    /// @param str I am the first param and i am the string who will be printed
    /// @return int The success value
    ///
```

* No functions should have documentation within .cpp files except static functions.

Any undocumented elements will lead to the refusal of the PR.


### Coding Style

For the coding style, there is no proper rules except one :
Everybody working on the project with you must be able to understand on what you are working within minutes. If you can split a function in two, you must do it !