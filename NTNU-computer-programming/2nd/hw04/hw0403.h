#pragma once

#include "lib/array.h"
#include "lib/string.h"
#include "lib/fileio.h"

#define STD_COLOR "\x1b[37;40m"
#define KEYBOARD_COLOR "\x1b[34;40m"

const char *C[44] = 
{
    "auto","break","case","char",
    "const","continue","default","do",
    "double","else","enum","extern",
    "float","for","goto","if",
    "inline","int","long","register",
    "restrict","return","short","signed",
    "sizeof","static","struct","switch",
    "typedef","union","unsigned","void",
    "volatile","while","_Alignas","_Alignof",
    "_Atomic","_Bool","_Complex","_Generic",
    "_Imaginary","_Noreturn","_Static_assert","_Thread_local"
};

const char *C_Sharp[107] = 
{
    "abstract","as","base","bool",
    "break","byte","case","catch",
    "char","checked","class","const",
    "continue","decimal","default","delegate",
    "do","double","else","enum",
    "event","explicit","extern","false",
    "finally","fixed","float","for",
    "foreach","goto","if","implicit",
    "in","int","interface","internal",
    "is","lock","long","namespace",
    "new","null","object","operator",
    "out","override","params","private",
    "protected","public","readonly","ref",
    "return","sbyte","sealed","short",
    "sizeof","stackalloc","static","string",
    "struct","switch","this","throw",
    "true","try","typeof","uint",
    "ulong","unchecked","unsafe","ushort",
    "using","virtual","void","volatile",
    "while","add","alias","ascending",
    "async","await","by","descending",
    "dynamic","equals","from","get",
    "global","group","into","join",
    "let","nameof","notnull","on",
    "orderby","partial","remove","select",
    "set","unmanaged","value","var",
    "when","where","yield"
};

const char *Cpp[84] = 
{
    "alignas","alignof","asm","auto",
    "bool","break","case","catch",
    "char","char16_t","char32_t","class",
    "const","constexpr","const_cast","continue",
    "decltype","default","delete","do",
    "double","dynamic_cast","else","enum",
    "explicit","export","extern","false",
    "float","for","friend","goto",
    "if","inline","int","long",
    "mutable","namespace","new","noexcept",
    "nullptr","operator","private","protected",
    "public","register","reinterpret_cast","return",
    "short","signed","sizeof","static",
    "static_assert","static_cast","struct","switch",
    "template","this","thread_local","throw",
    "true","try","typedef","typeid",
    "typename","union","unsigned","using",
    "virtual","void","volatile","wchar_t",
    "while","and","and_eq","bitand",
    "bitor","compl","not","not_eq",
    "or","or_eq","xor","xor_eq"
};

const char *Dart[33] =
{
    "assert","break","case","catch",
    "class","const","continue","default",
    "do","else","enum","extends",
    "false","final","finally","for",
    "if","in","is","new",
    "null","rethrow","return","super",
    "switch","this","throw","true",
    "try","var","void","while",
    "with"
};

const char *Elixir[15] =
{
    "true","false","nil","when",
    "and","or","not","in",
    "fn","do","end","catch",
    "rescue","after","else"
};

const char *Erlang[27] =
{
    "after","and","andalso","band",
    "begin","bnot","bor","bsl",
    "bsr","bxor","case","catch",
    "cond","div","end","fun",
    "if","let","not","of",
    "or","orelse","receive","rem",
    "try","when","xor"
};

const char *Fortran[103] =
{
    "abstract","allocatable","allocate","assign",
    "associate","asynchronous","backspace","bind",
    "block","blockdata","call","case",
    "class","close","codimension","common",
    "contains","contiguous","continue","critical",
    "cycle","data","deallocate","deferred",
    "dimension","do","doconcurrent","elemental",
    "else","elseif","elsewhere","end",
    "endfile","endif","entry","enum",
    "enumerator","equivalence","errorstop","exit",
    "extends","external","final","flush",
    "forall","format","function","generic",
    "goto","if","implicit","import",
    "include","inquire","intent","interface",
    "intrinsic","lock","module","namelist",
    "non_overridable","nopass","nullify","only",
    "open","operator","optional","parameter",
    "pass","pause","pointer","print",
    "private","procedure","program","protected",
    "public","pure","read","recursive",
    "result","return","rewind","rewrite",
    "save","select","sequence","stop",
    "submodule","subroutine","syncall","syncimages",
    "syncmemory","target","then","unlock",
    "use","value","volatile","wait",
    "where","while","write"
};

const char *Go[25] = 
{
    "break","case","chan","const",
    "continue","default","defer","else",
    "fallthrough","for","func","go",
    "goto","if","import","interface",
    "map","package","range","return",
    "select","struct","switch","type",
    "var"
};

const char *JS[38] =
{
    "await","break","case","catch",
    "class","const","continue","debugger",
    "default","delete","do","else",
    "enum","export","extends","false",
    "finally","for","function","if",
    "import","in","instanceof","new",
    "null","return","super","switch",
    "this","throw","true","try",
    "typeof","var","void","while",
    "with","yield"
};

const char *Java[51] =
{
    "abstract","assert","boolean","break",
    "byte","case","catch","char",
    "class","const","continue","default",
    "do","double","else","enum",
    "extends","final","finally","float",
    "for","if","goto","implements",
    "import","instanceof","int","interface",
    "long","native","new","package",
    "private","protected","public","return",
    "short","static","strictfp","super",
    "switch","synchronized","this","throw",
    "throws","transient","try","void",
    "volatile","while","_"
};

const char *Kotlin[79] =
{
    "as","as?","break","class",
    "continue","do","else","false",
    "for","fun","if","in",
    "!in","interface","is","!is",
    "null","object","package","return",
    "super","this","throw","true",
    "try","typealias","typeof","val",
    "var","when","while","by",
    "catch","constructor","delegate","dynamic",
    "field","file","finally","get",
    "import","init","param","property",
    "receiver","set","setparam","where",
    "actual","abstract","annotation","companion",
    "const","crossinline","data","enum",
    "expect","external","final","infix",
    "inline","inner","internal","lateinit",
    "noinline","open","operator","out",
    "override","private","protected","public",
    "reified","sealed","suspend","tailrec",
    "vararg","field","it"
};

const char *Lua[22] =
{
    "and","break","do","else",
    "elseif","end","false","for",
    "function","goto","if","in",
    "local","nil","not","or",
    "repeat","return","then","true",
    "until","while"
};

const char *MATLAB[20] =
{
    "break","case","catch","classdef",
    "continue","else","elseif","end",
    "for","function","global","if",
    "otherwise","parfor","persistent","return",
    "spmd","switch","try","while"
};

const char *Objective_C[85] =
{
    "asm","auto","break","case",
    "char","const","continue","default",
    "do","double","else","enum",
    "extern","float","for","goto",
    "if","inline","int","long",
    "register","restrict","return","short",
    "signed","sizeof","static","struct",
    "switch","typedef","union","unsigned",
    "void","volatile","while","_Bool",
    "_Complex","__block","Imaginary","id",
    "Class","SEL","IMP","BOOL",
    "nil","Nil","YES","NO",
    "self","super","_cmd","__strong",
    "__weak","__autoreleasing","__unsafe_unretained","oneway",
    "In","out","inout","bycopy",
    "byref","@autoreleasepool","@interface","@implementation",
    "@protocol","@end","@private","@protected",
    "@public","@package","@try","@throw",
    "@catch()","@finally","@property","@synthesize",
    "@dynamic","@class","@selector()","@protocol()",
    "@required","@optional","@encode","@\"string\"",
    "@synchronized()"
};

const char *PHP[69] =
{
    "__halt_compiler()","abstract","and","array()",
    "as","break","callable","case",
    "catch","class","clone","const",
    "continue","declare","default","die()",
    "do","echo","else","elseif",
    "empty()","enddeclare","endfor","endforeach",
    "endif","endswitch","endwhile","eval()",
    "exit()","extends","final","finally",
    "fn","for","foreach","function",
    "global","goto","if","implements",
    "include","include_once","instanceof","insteadof",
    "interface","isset()","list()","namespace",
    "new","or","print","private",
    "protected","public","require","require_once",
    "return","static","switch","throw",
    "trait","try","unset()","use",
    "var","while","xor","yield",
    "yieldfrom"
};

const char *Python[35] =
{
    "False","None","True","and",
    "as","assert","async","await",
    "break","class","continue","def",
    "del","elif","else","except",
    "finally","for","from","global",
    "if","import","in","is",
    "lambda","nonlocal","not","or",
    "pass","raise","return","try",
    "while","with","yield"
};

const char *R[21] =
{
    "...","..1","FALSE","Inf",
    "NA","NA_character_","NA_complex_","NA_integer_",
    "NA_real_","NaN","NULL","TRUE",
    "break","else","for","function",
    "if","in","next","repeat",
    "while"
};

const char *Ruby[41] =
{
    "_ENCODING_","_LINE_","_FILE_","BEGIN",
    "END","alias","and","begin",
    "break","case","class","def",
    "defined?","do","else","elsif",
    "end","ensure","false","for",
    "if","in","module","next",
    "nil","not","or","redo",
    "rescue","retry","return","self",
    "super","then","true","undef",
    "unless","until","when","while",
    "yield"
};

const char *Rust[53] =
{
    "as","break","const","continue",
    "crate","else","enum","extern",
    "false","fn","for","if",
    "impl","in","let","loop",
    "match","mod","move","mut",
    "pub","ref","return","self",
    "Self","static","struct","super",
    "trait","true","type","unsafe",
    "use","where","while","async",
    "await","dyn","abstract","become",
    "box","do","final","macro",
    "override","priv","typeof","unsized",
    "virtual","yield","try","union",
    "\'static"
};

const char *Scala[40] =
{
    "abstract","case","catch","class",
    "def","do","else","extends",
    "false","final","finally","for",
    "forSome","if","implicit","import",
    "lazy","macro","match","new",
    "null","object","override","package",
    "private","protected","return","sealed",
    "super","this","throw","trait",
    "try","true","type","val",
    "var","while","with","yield"
};

const char *Swift[97] =
{
    "associatedtype","class","deinit","enum",
    "extension","fileprivate","func","import",
    "init","inout","internal","let",
    "open","operator","private","protocol",
    "public","rethrows","static","struct",
    "subscript","typealias","var","break",
    "case","continue","default","defer",
    "do","else","fallthrough","for",
    "guard","if","in","repeat",
    "return","switch","where","while",
    "as","Any","catch","false",
    "is","nil","super","self",
    "Self","throw","throws","true",
    "try","_","#available","#colorLiteral",
    "#column","#else","#elseif","#endif",
    "#error","#file","#filePath","#fileLiteral",
    "#function","#if","#imageLiteral","#line",
    "#selector","#sourceLocation","#warning","associativity",
    "convenience","dynamic","didSet","final",
    "get","infix","indirect","lazy",
    "left","mutating","none","nonmutating",
    "optional","override","postfix","precedence",
    "prefix","Protocol","required","right",
    "set","Type","unowned","weak",
    "willSet"
};

const char *Visual_Basic[217] =
{
    "AddHandler","AddressOf","Alias","And",
    "AndAlso","As","Boolean","ByRef",
    "Byte","ByVal","Call","Case",
    "Catch","CBool","CByte","CChar",
    "CDate","CDbl","CDec","Char",
    "CInt","Class","CLng","CObj",
    "Const","Continue","CSByte","CShort",
    "CSng","CStr","CType","CUInt",
    "CULng","CUShort","Date","Decimal",
    "Declare","Default","Delegate","Dim",
    "DirectCast","Do","Double","Each",
    "Else","ElseIf","End","EndIf",
    "Enum","Erase","Error","Event",
    "Exit","False","Finally","For",
    "ForEach","Friend","Function","Get",
    "GetType","GetXMLNamespace","Global","GoSub",
    "GoTo","Handles","If","If()",
    "Implements","Imports","In","Inherits",
    "Integer","Interface","Is","IsNot",
    "Let","Lib","Like","Long",
    "Loop","Me","Mod","Module",
    "MustInherit","MustOverride","MyBase","MyClass",
    "NameOf","Namespace","Narrowing","New",
    "Next","Not","Nothnig","NotInheritable",
    "NotOverridable","Object","Of","On",
    "Operator","Option","Optional","Or",
    "OrElse","Out","Overloads","Overridable",
    "Overrides","ParamArray","Partial","Private",
    "Property","Protected","Public","RaiseEvent",
    "ReadOnly","ReDim","REM","RemoveHandler",
    "Resume","Return","SByte","Select",
    "Set","Shadows","Shared","Short",
    "Single","Static","Step","Stop",
    "String","Structure","Sub","SyncLock",
    "Then","Throw","To","True",
    "Try","TryCast","TypeOf","UInteger",
    "ULong","UShort","Using","Variant",
    "Wend","When","While","Widening",
    "With","WithEvents","WriteOnly","Xor",
    "#Const","#Else","#ElseIf","#End",
    "#If","=","&","&=",
    "*","*=","/","/=",
    "\\","=","^","^=",
    "+","+=","-","-=",
    ">>",">>=","<<","<<=",
    "Aggregate","Ansi","Assembly","Async",
    "Auto","Await","Binary","Compare",
    "Custom","Distinct","Equals","Explicit",
    "From","GroupBy","GroupJoin","Into",
    "IsFalse","IsTrue","Iterator","Join",
    "Key","Mid","Off","OrderBy",
    "Preserve","Skip","SkipWhile","Strict",
    "Take","TakeWhile","Text","Unicode",
    "Until","Where","Yield","#ExternalSource",
    "#Region"
};

void print_code_highlighter(char *filename,bool show_linenum,bool show_color,char *language)
{
    char **keyboard = (char**)malloc(1000);
    uint32_t keyboard_count = 0;
    if(is_str_same(language,"C"))
    {
        memcpy(keyboard,C,get_array_length(C)*sizeof(char*));
        keyboard_count = get_array_length(C);
    }
    else if(is_str_same(language,"C#"))
    {
        memcpy(keyboard,C_Sharp,get_array_length(C_Sharp)*sizeof(char*));
        keyboard_count = get_array_length(C_Sharp);
    }
    else if(is_str_same(language,"C++"))
    {
        memcpy(keyboard,Cpp,get_array_length(Cpp)*sizeof(char*));
        keyboard_count = get_array_length(Cpp);
    }
    else if(is_str_same(language,"Dart"))
    {
        memcpy(keyboard,Dart,get_array_length(Dart)*sizeof(char*));
        keyboard_count = get_array_length(Dart);
    }
    else if(is_str_same(language,"Elixir"))
    {
        memcpy(keyboard,Elixir,get_array_length(Elixir)*sizeof(char*));
        keyboard_count = get_array_length(Elixir);
    }
    else if(is_str_same(language,"Erlang"))
    {
        memcpy(keyboard,Erlang,get_array_length(Erlang)*sizeof(char*));
        keyboard_count = get_array_length(Erlang);
    }
    else if(is_str_same(language,"Fortran"))
    {
        memcpy(keyboard,Fortran,get_array_length(Fortran)*sizeof(char*));
        keyboard_count = get_array_length(Fortran);
    }
    else if(is_str_same(language,"Go"))
    {
        memcpy(keyboard,Go,get_array_length(Go)*sizeof(char*));
        keyboard_count = get_array_length(Go);
    }
    else if(is_str_same(language,"JS"))
    {
        memcpy(keyboard,JS,get_array_length(JS)*sizeof(char*));
        keyboard_count = get_array_length(JS);
    }
    else if(is_str_same(language,"Java"))
    {
        memcpy(keyboard,Java,get_array_length(Java)*sizeof(char*));
        keyboard_count = get_array_length(Java);
    }
    else if(is_str_same(language,"Kotlin"))
    {
        memcpy(keyboard,Kotlin,get_array_length(Kotlin)*sizeof(char*));
        keyboard_count = get_array_length(Kotlin);
    }
    else if(is_str_same(language,"Lua"))
    {
        memcpy(keyboard,Lua,get_array_length(Lua)*sizeof(char*));
        keyboard_count = get_array_length(Lua);
    }
    else if(is_str_same(language,"MATLAB"))
    {
        memcpy(keyboard,MATLAB,get_array_length(MATLAB)*sizeof(char*));
        keyboard_count = get_array_length(MATLAB);
    }
    else if(is_str_same(language,"Objective-C"))
    {
        memcpy(keyboard,Objective_C,get_array_length(Objective_C)*sizeof(char*));
        keyboard_count = get_array_length(Objective_C);
    }
    else if(is_str_same(language,"PHP"))
    {
        memcpy(keyboard,PHP,get_array_length(PHP)*sizeof(char*));
        keyboard_count = get_array_length(PHP);
    }
    else if(is_str_same(language,"Python"))
    {
        memcpy(keyboard,Python,get_array_length(Python)*sizeof(char*));
        keyboard_count = get_array_length(Python);
    }
    else if(is_str_same(language,"R"))
    {
        memcpy(keyboard,R,get_array_length(R)*sizeof(char*));
        keyboard_count = get_array_length(R);
    }
    else if(is_str_same(language,"Ruby"))
    {
        memcpy(keyboard,Ruby,get_array_length(Ruby)*sizeof(char*));
        keyboard_count = get_array_length(Ruby);
    }
    else if(is_str_same(language,"Rust"))
    {
        memcpy(keyboard,Rust,get_array_length(Rust)*sizeof(char*));
        keyboard_count = get_array_length(Rust);
    }
    else if(is_str_same(language,"Scala"))
    {
        memcpy(keyboard,Scala,get_array_length(Scala)*sizeof(char*));
        keyboard_count = get_array_length(Scala);
    }
    else if(is_str_same(language,"Swift"))
    {
        memcpy(keyboard,Swift,get_array_length(Swift)*sizeof(char*));
        keyboard_count = get_array_length(Swift);
    }
    else if(is_str_same(language,"Visual Basic"))
    {
        memcpy(keyboard,Visual_Basic,get_array_length(Visual_Basic)*sizeof(char*));
        keyboard_count = get_array_length(Visual_Basic);
    }
    char **text = NULL;
    int32_t row_count = read_text_file_2D(&text,filename);
    for(int i = 0; i < row_count;i++)
    {
        if(show_linenum)
        {
            printf(STD_COLOR"%8d  ",i+1);
        }
        if(show_color)
        {   
            for(int n=0;n<keyboard_count;n++)
            {
                uint32_t *index = NULL;
                uint32_t count = str_find(text[i],keyboard[n],&index);
                for(int j = 0,offset = 0; j < count; j++)
                {
                    str_insert(&(text[i]),KEYBOARD_COLOR,index[j]+offset);
                    offset += strlen(KEYBOARD_COLOR);
                    str_insert(&(text[i]),STD_COLOR,index[j]+strlen(keyboard[n])+offset);
                    offset += strlen(STD_COLOR);
                }
                
            }
        }
        printf(STD_COLOR"%s",text[i]);
    }
    free(text);
    free(keyboard);
}