#include "section.h"
#include "scene.h"
#include <cassert>
#include "parse_exception.h"
#include <set>
#include "parse_tree_visitor.h"

namespace fabula
{
    namespace parsing
    {
        namespace node
        {
//            Section::Section() {}

//            Section::~Section()
//            {
//				for (auto it = mScenes.begin(); it != mScenes.end(); ++it)
//                    delete it->second;
//				for (auto it = mSubsections.begin(); it != mSubsections.end(); ++it)
//					delete it->second;
//            }

//            void Section::add(Section* s)
//            {
//				assert(s);
//				if (hasScene(s->name()))
//					throw SemanticException("A scene with such a name already exists!");
//				if (hasSubsection(s->name()))
//					throw SemanticException("A subsection with such a name already exists!");
//	            mSubsections[s->name()] = s;
//            }

//            void Section::add(Scene* s)
//            {
//				assert(s);
//				if (hasScene(s->name()))
//					throw SemanticException("A scene with such a name already exists!");
//				if (hasSubsection(s->name()))
//					throw SemanticException("A subsection with such a name already exists!");
//				mScenes[s->name()] = s;
//            }

//			ParseNode::NodeType Section::nodeType()
//			{
//				return NodeType::Section;
//			}

//			bool Section::hasSubsection (const std::string& name) const
//			{
//				return (bool)mSubsections.count(name);
//			}

//			bool Section::hasScene (const std::string& name) const
//			{
//				return (bool)mScenes.count(name);
//			}

//            std::shared_ptr<Section> Section::getSubsection(const std::string& name)
//			{
//				auto it = mSubsections.find(name);
//				if (it == mSubsections.end())
//					return nullptr;
//				else
//					return it->second;
//			}

//            std::shared_ptr<Scene> Section::getScene(const std::string& name)
//			{
//				auto it = mScenes.find(name);
//				if (it == mScenes.end())
//					return nullptr;
//				else
//					return it->second;
//			}

//            std::shared_ptr<Scene> Section::findStartScene()
//			{
//				if (hasScene("main"))
//					return getScene("main");
//				else for (auto s = sectionsBegin(); s != sectionsEnd(); ++s)
//				{
//					assert(s->second);
//                    auto sc = s->second->findStartScene();
//					if (sc)
//						return sc;
//				}

//				return nullptr;
//			}
        }
    }
}
