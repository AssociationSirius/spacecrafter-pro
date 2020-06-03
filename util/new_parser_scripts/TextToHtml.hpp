#ifndef TEXT_TO_HTML_HPP
#define TEXT_TO_HTML_HPP

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <iostream>

class TextToHtml {
public:
    TextToHtml(std::vector<std::string> _text);
	~TextToHtml();

    //On lit le vecteur d'entrée (inText)
    void lecture();

private:

    void transformation(std::string lines);
    std::string findBloc(std::string lines, std::string arg);
    void NameInHtml(std::string lines);
    void ArgumentInHtml(std::string lines);
    void ParameterInHtml(std::string lines);
    void ExempleInHtml(std::string lines);

    std::string ToHtml;

    std::vector<std::string> inText;
    std::vector<std::string> outText;
};

#endif