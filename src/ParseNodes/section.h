#pragma once

/**
  * @author Anima Seteine
  * @purpose This class holds the information about a section object. A section can contain scenes, or subsections.
  */

#include <string>
#include <map>
#include <memory>
#include "parse_node.h"

namespace fabula
{
	namespace parsing
    {
		class Writer;

		namespace node
        {
			class Scene;

		    class Section : public ParseNode
		    {
                template<class T>
                typename T::mapped_type getRecursiveX(T& member, const std::string& name, bool recursive) const
                {
                    auto it = member.find(name);
                    if(it != member.end())
                        return it->second;

                    if(!recursive)
                        return nullptr;

                    for(auto& p : subsections)
                    {
                        auto answer = p.second->getRecursiveX(member, name, true);
                        if(answer)
                            return answer;
                    }

                    return nullptr;
                }

                template<class T>
                bool hasRecursiveX(T& member, const std::string& name, bool recursive) const
                {
                    return (bool)getRecursiveX<T>(member, name, recursive);
                }

            public:

                std::string                                     name;
                std::map<std::string, std::shared_ptr<Scene>>   scenes;
                std::map<std::string, std::shared_ptr<Section>> subsections;

				/** Adds a child section, taking ownership of the argument. */
                void add(const std::shared_ptr<Scene>& s);

				/** Adds a child scene, taking ownership of the argument. */
                void add(const std::shared_ptr<Section>& s);

				/** Returns the corresponding node type of the class. */
                virtual NodeType nodeType();

                /** returns whether the section has a subsection with a given name. */
                bool hasSubsection (const std::string& name, bool recursive = false) const
                {
                    return (bool)hasRecursiveX(subsections, name, recursive);
                }

                /** returns whether the scene has a subsection with a given name. */
                bool hasScene (const std::string& name, bool recursive = false) const
                {
                    return (bool)hasRecursiveX(scenes, name, recursive);
                }

                /** Returns a subsection given a name, returning null if none exists. */
                Section* getSubsection(const std::string& name, bool recursive = false)
                {
                    return getRecursiveX(subsections, name, recursive).get();
                }

                /** Returns a scene given a name, returning null if none exists. */
                Scene* getScene(const std::string& name, bool recursive = false)
                {
                    return getRecursiveX(scenes, name, recursive).get();
                }

				/** Scans the section and any subsections for a scene with the name "main",
				  * and returns the first one found. Should be safe after the semantic checks. */
                Scene* findStartScene();

                bool hasChildWithName(const std::string& name, bool recursive = false);
		    };
		}
	}
}
