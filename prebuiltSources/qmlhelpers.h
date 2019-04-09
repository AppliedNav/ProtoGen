#ifndef QMLHELPERS_H
#define QMLHELPERS_H

#include <QObject>

#define QML_WRITABLE_PROPERTY(type, name, setter) \
    protected: \
        Q_PROPERTY(type name MEMBER m_##name WRITE setter NOTIFY name##Changed) \
    public: \
        void setter(const type &value) { \
            if (value != m_##name) { \
                m_##name = value; \
                emit name##Changed(); \
            } \
        } \
        const type& name() const { return m_##name; } \
    Q_SIGNALS: \
        void name##Changed(); \
    private: \
        type m_##name;

#define QML_WRITABLE_PROPERTY_INIT(type, name, setter, defaultValue) \
    protected: \
        Q_PROPERTY(type name MEMBER m_##name WRITE setter NOTIFY name##Changed) \
    public: \
        void setter(const type &value) { \
            if (value != m_##name) { \
                m_##name = value; \
                emit name##Changed(); \
            } \
        } \
        const type& name() const { return m_##name; } \
    Q_SIGNALS: \
        void name##Changed(); \
    private: \
        type m_##name = defaultValue;

#define QML_WRITABLE_PROPERTY_FLOAT(type, name, setter) \
    protected: \
        Q_PROPERTY(type name MEMBER m_##name WRITE setter NOTIFY name##Changed) \
    public: \
        void setter(type value) { \
            if (!qFuzzyCompare(value, m_##name)) { \
                m_##name = value; \
                emit name##Changed(); \
            } \
        } \
        const type& name() const { return m_##name; } \
    Q_SIGNALS: \
        void name##Changed(); \
    private: \
        type m_##name;

#define QML_WRITABLE_PROPERTY_FLOAT_INIT(type, name, setter, defaultValue) \
    protected: \
        Q_PROPERTY(type name MEMBER m_##name WRITE setter NOTIFY name##Changed) \
    public: \
        void setter(type value) { \
            if (!qFuzzyCompare(value, m_##name)) { \
                m_##name = value; \
                emit name##Changed(); \
            } \
        } \
        const type& name() const { return m_##name; } \
    Q_SIGNALS: \
        void name##Changed(); \
    private: \
        type m_##name = defaultValue;

#define QML_READABLE_PROPERTY(type, name, setter, defaultValue) \
    protected: \
        Q_PROPERTY(type name MEMBER m_##name NOTIFY name##Changed) \
    public: \
        void setter(const type &value) { \
            if (value != m_##name) { \
                m_##name = value; \
                emit name##Changed(); \
            } \
        } \
    Q_SIGNALS: \
        void name##Changed(); \
    private: \
        type m_##name = defaultValue;

#define QML_READABLE_PROPERTY_NO_INIT(type, name, setter) \
    protected: \
        Q_PROPERTY(type name MEMBER m_##name NOTIFY name##Changed) \
    public: \
        void setter(const type &value) { \
            if (value != m_##name) { \
                m_##name = value; \
                emit name##Changed(); \
            } \
        } \
    Q_SIGNALS: \
        void name##Changed(); \
    private: \
        type m_##name;

#define QML_CONSTANT_PROPERTY(type, name, defaultValue) \
    protected: \
        Q_PROPERTY(type name MEMBER m_##name CONSTANT) \
    private: \
        const type m_##name = defaultValue;

#define QML_CONSTANT_PROPERTY_NO_INIT(type, name) \
    protected: \
        Q_PROPERTY(type name MEMBER m_##name CONSTANT) \
    private: \
        const type m_##name;

#define QML_CONSTANT_PROPERTY_PTR(type, name) \
    protected: \
        Q_PROPERTY(type* name MEMBER m_##name CONSTANT) \
    public: \
        type& name() { return *m_##name; } \
    private: \
        type* m_##name = new type();

// NOTE : to avoid "no suitable class found" MOC note
class QmlProperty : public QObject { Q_OBJECT };

#endif // QMLHELPERS_H
