#ifndef LEVELGENERATOR_H
#define LEVELGENERATOR_H

#include <QList>
#include <functional>
#include "levelobjectcreator.h"
#include "abstractobjectcontroller.h"

class EngineInterface;

class LevelGenerator
{
public:
    LevelGenerator();
    void proceed(Rect visualRect);
    void addCreators(const std::vector<LevelObjectCreator *> &list);

    void setCreateHandler(const std::function<uint32_t(std::string)> &createHandler);
    void setDeleteHandler(const std::function<bool(uint32_t)> &deleteHandler);

private:
    std::function<uint32_t(std::string type)> m_createHandler = nullptr;
    std::function<bool(uint32_t)> m_deleteHandler = nullptr;
    std::vector<LevelObjectCreator*> m_creators;
};

#endif // LEVELGENERATOR_H
