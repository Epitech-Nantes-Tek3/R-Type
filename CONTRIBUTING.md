## Development Rules

The rules to contribute to the R-Type project are described below.
Please follow the indicated rules to contribute in the most efficient way !


### Issue Rules

When creating an issue, you must follow the given format :

* The name of the issue must have an action verb and a title

```bash
    Create the Contributing.md
```

* Describing the issue is mandatory and usefull for everyone. Try to be concise with the features which will be added on the project. Using a template for your issue is recommended.

* Add a label to clarify the issue. If there is no label existing or corresponding to your issue, create one and describe it.

* Take a moment to link the issue with the project, if it hasn't been done automatically.


### Branch Rules

The branch name should consider the issue title and the issue number in its name. The issue's number must come first.

Example:

```bash
    git checkout -b 2-Create-The-Contributing.md
```

You must make one branch per issue.

Try to push as regularly as possible so everyone can see where you are at.
When first committing on a branch, it is recommended to open a PR draft, so it will be easier for your mates to see where you are at.


### Coding Style

For the coding style, there are some rules you need to follow:
 - Everybody working on the project with you must be able to understand on what you are working within minutes. If you can split a function in two, you must do it !
 - Your code must respect the Clang format. It's necessary to be able to compile on Windows. While coding, press at the same time CTRL+MAJ+I to apply the format !


### Documentation Rules

We use Doxygen for documentation, and in order to allow the proper deployment of the documentation, please respect the following rules:


* Please document your defines and typedefs as follows :

```bash
    /// @brief The maximum height of the displayed window
    #define MAXIMUM_HEIGTH 600
```

* Please document your functions in the header as follows:

```bash
    /// @brief Print a string
    /// @param str I am the first param and i am the string who will be printed
    /// @return int The success value
    /// @throw an Exception if the given string is empty
```

* No functions should have documentation within .cpp files except static functions.

Any undocumented elements will lead to the refusal of the PR.


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


### Testing Rules

When something can be verified by a test, we will be looking for tests in your PR.

To compile your tests, the corresponding CMakeLists.txt should look like this:
```bash
    set (SRC_ROOT ${PROJECT_SOURCE_DIR}/tests/unit_tests)

    set(TEST_SRC_ROOT
        ${SRC_ROOT}/very_basic_test.cpp
    )

    ## Documented Example ##
    create_test(
        ## First, the name of the test ##
        TEST_NAME very_basic_test
        ## Second, the sources for the test ##
        TEST_SRC ${TEST_SRC_ROOT}
        ## Last, the depenancies (necessary libraries) ##
        ## In this case none, otherwise add TEST_DEPS ${DEPENDANCY_NAME}
    )
```

And the file with all the unit tests will look like this:
```bash
    #include <criterion/criterion.h>

    /// @brief Very Basic Test
    Test(Basic, some_basics_tests)
    {
        cr_assert_eq(42, 42);
    }
```

For more details, you can go from the project's root to tests/unit_tests directory.

If you're in functionnal tests, please add a bash/bat script to execute them.

The lack of test in your code can be one of the reasons of refusing a PR.


### Pull Request Rules

When your work is done on a branch, you must make a pull request.

The name is the same for the branch.
However, you must write a description as a reminder of what you have done.
It may be all about the issue, but often you have unexpected fixes.

For the reviewers, prioritize the people who can really help you with your work.

You must have at least 2 reviewers who approve your pull request.

Try not to exceed 24 hours before reading your PRs.

It is obviously forbidden to approve a merge until all the reviewers have accepted the PR as well as the success of the workflows.