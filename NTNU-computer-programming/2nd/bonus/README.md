> **Student ID: 41047035S**  
> **Student Name: 林昕鋭**  
> **Teacher Name: 紀博文**  
> **Finish Date: 2022/06/05**

# Doxygen for the beginner

## What is Doxygen?
**Generate documentation from source code**  
Doxygen is the de facto standard tool for generating documentation from annotated C++ sources, but it also supports other popular programming languages such as C, Objective-C, C#, PHP, Java, Python, IDL (Corba, Microsoft, and UNO/OpenOffice flavors), Fortran, and to some extent D. Doxygen also supports the hardware description language VHDL.

> [Doxygen-offical-website](https://doxygen.nl/index.html)

## How to download Doxygen
Make sure your os environment. Following the step below:

- Windows
```bash
# Just download it from official website and run setup.exe
```

- Mac
```bash
brew install doxygen
```

- Linux
```bash
git clone https://github.com/doxygen/doxygen.git
cd doxygen
mkdir build
cd build
cmake -G "Unix Makefiles" ..
make
make install
```

## Get started with Doxygen
In this tutorial, I will use Mac m1 version to introduce. And Linux's steps basically same with Mac's ones.

#### Step 1 : Initialize Doxygen configure file
```bash
doxygen -g
```
After run this command, you will get a file named "Doxyfile"
> If add option [-s], you will get none-comment simple one.

#### Step 2 : Edit TAG in Doxyfile
There are some TAGs in Doxyfile that can edit information. By these TAGs, it will effect your generating documentation difference.  

List some more important TAGs below:
- **PROJECT_NAME** : As its names.
- **OUTPUT_DIRECTORY** : Output path of generating document. If you do not input any value, the output path will be current path.
- **OUTPUT_LANGUAGE** : Output language format. 
- **OPTIMIZE_OUTPUT_FOR_C** : If your document is c language file, it must be YES value.
- **GENERATE_TREEVIEW** : Generate tree structure format. It will showed left side.
- **EXTRACT_ALL** : Even though these documents have no content. It will show imformation to generating file.

> About top of this note that I explane TAGs. These are also changed value from defualt file that I modified.

For more TAGs imformation, please follow the link below :  
https://www.doxygen.nl/manual/config.html

#### Step 3 : Standard comment format and parameter
To let Doxygen can analysis your file. It is needed to add some comment format and parameter. 
- **Comment Format** 
    - New Lines
    ```
    /**
    *   ...Comments...
    *   ...Comments...
    *   ...Comments...
    */
    ```

    - Single Line
    ```
    /** ...Comments... */
    ```
    ```
    /// ...Comments...
    ```

    - Same Line with Code
    ```
    /**< ...Comments... */    
    ```
    ```
    ///< ...Comments...
    ```

- **Parameter**
    - @brief (\brief) : a short description
    - @file (\file) : target file name (always be current file name.) (write at top of file)
    - @author (\author) : author name (write at top of file)
    - @date (\date) : date (write at top of file)
    - @param[in/out] (\param[in/out]) : function parameter target name

> About top of this note that I explane parameter. These are also added by me.

For more Comment anf Parameter imformation, please follow two links below :  
https://www.doxygen.nl/manual/docblocks.html
https://www.doxygen.nl/manual/commands.html
#### Step 4 : Generate document
```bash
doxygen Doxyfile
```
After run this command, you could view your document by your path of **OUTPUT_DIRECTORY** TAG in Doxyfile. In "html" directory, there is a file named "index.html". Open it and you can view your document.