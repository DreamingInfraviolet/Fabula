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
                std::string                                     mName;
                std::map<std::string, std::shared_ptr<Scene>>   mScenes;
                std::map<std::string, std::shared_ptr<Section>> mSubsections;
			public:


				/** Initialises an empty section with no children. */
				Section();

				/** Destroys all child elements. */
				~Section();

				/** Sets the name of the section. */
				void name(const std::string& name);

				/** Returns the name of the section. */
				std::string name() const;

				/** Returns start scenes iterator. */
                decltype(mScenes)& scenes();

				/** Returns the start subsections iterator. */
                decltype(mSubsections)& sections();

				/** Adds a child section, taking ownership of the argument. */
				void add(Section* s);

				/** Adds a child scene, taking ownership of the argument. */
				void add(Scene* s);

				/** Returns the corresponding node type of the class. */
				virtual NodeType nodeType();

				/** returns whether the section has a subsection with a given name. */
				bool hasSubsection (const std::string& name) const;

				/** returns whether the scene has a subsection with a given name. */
				bool hasScene (const std::string& name) const;

				/** Returns a subsection given a name, returning null if none exists. */
                std::shared_ptr<Section> getSubsection(const std::string& name);

				/** Returns a scene given a name, returning null if none exists. */
                std::shared_ptr<Scene> getScene(const std::string& name);

				/** Scans the section and any subsections for a scene with the name "main",
				  * and returns the first one found. Should be safe after the semantic checks. */
                std::shared_ptr<Scene> findStartScene();
		    };
		}
	}
}
