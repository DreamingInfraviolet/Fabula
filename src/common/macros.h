#pragma oce

#define FABULA_MEMBER(type, name) type m_##name;

#define FABULA_MEMBER_GET_(type, name) type& ##name() const { return m_##name; }
#define FABULA_MEMBER_SET_(type, name) void ##name(const type& t) { m_##name = t; }

#define FABULA_MEMBER_GET(type, name) private: FABULA_MEMBER(type, name); public: FABULA_MEMBER_GET_(type, name)
#define FABULA_MEMBER_SET(type, name) private: FABULA_MEMBER(type, name); public: FABULA_MEMBER_SET_(type, name)

#define FABULA_MEMBER_GET_SET(type, name) private: FABULA_MEMBER(type, name);
