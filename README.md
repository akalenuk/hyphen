Hyphen-notation examples
======

Hyphen-notation is the way to build verbose and expressive language constructs using host language syntax capabilities. It can be used to improve code readability or even to build an embedded domain-specific language. Consider this piece of code:

    the IDsToCheck = {"outOfBounds", "negativeIndex", "fakeError"};
    
    the Text = loaded-from-"errorlist_example.xml";
    
    the Lines = Text-split-with-"<error id=";
    the LinesWithoutXMLHeader = Lines-elements-(from-2-to-(last-of-Lines));
    for( the Line : LinesWithoutXMLHeader ){
        the ErrorID = (Line-split-with-" ")[1];
        memorize-ErrorID;
    }
    
    the Report = "Checked error IDs:";
    
    for( the ID : IDsToCheck ){
        if( remember-(ID-in-quotemarks) ){
            Report = Report & "\n\t" & ID & " is in error list;";
        }else{
            Report = Report & "\n\t" & ID & " is not.";
        }
    }
    
    save-Report-to-"checked_errors.txt";
    print-it;

It's rather plain to see what is it for. It reads some list of errors in XML form and checks if it has some particular errors in it. It is verbose yet concise due to the very high level of its constructs. Kind of nice readable mini-languagge.

And yet it is plain C++.

C++11 to be exact. But it doesn't have to be exactly C++, all you need to get your hyphen-notation constructs implemented in a language of your choice is to overload operator `-` for a bunch of trivial types. Of course operator overloading means you have to be able to make your own types as well. So potentially C#, Python, PHP and even Fortran or Ada can adopt hyphen-notation with little effort.

Let's see how it is done. Consider this example: `Line-split-by-" "`. It takes a text string and makes an array of words out of, so "Hello, world!" becomes {"Hello,", "world!"}. Now look:

    struct With {} with;
    
    struct a_Split_with_X{
        the m_a;
        a_Split_with_X(the a) : m_a(a) {}
        the operator-(the b){
            return m_a.split_with(b);
        }
    };
    
    struct a_Split_X{
        the m_a;
        a_Split_X(the a) : m_a(a) {}
        a_Split_with_X operator-(With with){
            return a_Split_with_X(m_a);
        }
    };
    
    struct X_Split{
    } split;
    a_Split_X operator-(the a, X_Split x_split){
        return a_Split_X(a);
    }

Structure `With` can really be any structure you want. Empty is just fine. All you need - is to declare an object named `with` of any specific type.

Structure `a_Split_with_X` is a container for actual code. It has constructor which gets its first argument, like "Hello, world!" string; and an operator '-' overloaded to get actual work done. When you call an object of type `a_Split_with_X` with minus `b`, you have your `return m_a.split_with(b);` called.

Structure `a_Split_X` also has a constructor to recieve "Hello, world!" string, but when object of type `a_Split_X` is called with minus `with`, remember we declared it just then, it returns a freshly instanced object of type `a_Split_with_X` with "Hello, world!" passed to it via constructor.

Structure `X_Split` is empty, but it has an external operator of type `the`. Nevermind the type, this `the` is just a variant that accepts arrays, it's not that important right now. What is important, there is an object of type `X_Split` namely `split`. Being called with operator `-` on the left, it receives the argument and returns an instance of `a_Split_X` with it.

You can see, these are kind of chained. But actually the topology of these instantiations doesn't have to be that simple. You can build a hyphen-construct that can accept 'with' or 'without' for a_Split_X and that would be a tree with two possible code chunks called at the end. Or instead of 'with' you can accept another string, concatenate it to `m_a` and instance yet another `a_Split_X`. That would be a cycle; you can make theoretically endless hyphen-constructs with these.

Hyphen-constructs are very malleable in this regard. There are some limitations though. For instance, you can not use reserved words, such as `and` or `for`, which is little discouraging. 

Nevertheless, I see a huge potential in this technique. Having nice mini-language code in the same environment as the general purpose language with all its libraries is indeed exciting. You can debug and profile it with the same set of tools, and you also can grow this mini-language the way you grow any other code. You don't need to adopt any scripting language or adapt any parser-generator, just add one hyphen-construct at the time. It's natural way to grow a language.

I've prepared two little demos for it. One is in `console-demo` folder, and another in the `game-of-15`. `game-of-15` also uses HGE. Take a look at hyphen-code pieces in them:
- https://github.com/akalenuk/hyphen/blob/master/game-of-15/main.cpp#L38
- https://github.com/akalenuk/hyphen/blob/master/game-of-15/main.cpp#L99
- https://github.com/akalenuk/hyphen/blob/master/console-demo/main.cpp
