#include "tool.h"

Tool::Tool()
{

}

void Tool::setColor(QColor color){
    brushPen.setColor(color);
}

void Tool::setBrushSize(int size){
    brushPen.setWidth(size);
}

void Tool::setSelectedToolType(ToolType type){
    selectedToolType = type;
}

QColor Tool::getFillColor(){
    return brushPen.color();
}

QPen* Tool::getBrushPen(){
    return &brushPen;
}

ToolType Tool::getSelectedToolType() {
    return selectedToolType;
}




