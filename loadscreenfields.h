//
// Created by phtran on 14/05/2016.
//

#ifndef FRONTEND_LOADSCREENFIELDS_H
#define FRONTEND_LOADSCREENFIELDS_H

#include <vector>
#include <string>
#include <memory>


namespace UI
{
    class Screen;
    class ScreenField;

}

void loadScreenFields(UI::Screen&, std::vector<std::shared_ptr<UI::ScreenField> >&, const std::string&);

#endif //FRONTEND_LOADSCREENFIELDS_H
