#ifndef QMLHELPERS_H
#define QMLHELPERS_H

#include <QObject>
#include <QVariant>

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
        type m_##name = 0;

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
        type m_##name = 0;

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

#define QML_CONSTANT_PROPERTY_PTR(type, name) \
    protected: \
        Q_PROPERTY(type* name MEMBER m_##name CONSTANT) \
    public: \
        type& name() { return *m_##name; } \
    private: \
        type* m_##name = new type();

#define QML_WRITABLE_PROPERTY_PTR(type, name, setterInType, setter) \
    protected: \
        Q_PROPERTY(type* name MEMBER m_##name NOTIFY name##Changed) \
    public: \
        void setter(const setterInType *value) { \
            m_##name->setData(value); \
            emit name##Changed(); \
        } \
        void name(setterInType *value) const { \
            m_##name->getData(value); \
        } \
    Q_SIGNALS: \
        void name##Changed(); \
    private: \
        type* m_##name = new type();

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(*arr))

#define QML_WRITABLE_PROPERTY_ARRAY_FLOAT(name, setter, size) \
    protected: \
        Q_PROPERTY(QVariantList name MEMBER m_##name NOTIFY name##Changed) \
    public: \
        void setter(const float *value, int numElem) { \
            m_##name.clear(); \
            for (int i = 0; i < numElem; ++i) m_##name.append(value[i]); \
            emit name##Changed(); \
        } \
        void name(float *value, int numElem) const { \
            for (int i = 0; i < numElem; ++i) value[i] = m_##name.at(i).toFloat(); \
        } \
    Q_SIGNALS: \
        void name##Changed(); \
    private: \
        QVariantList m_##name;

// NOTE : to avoid "no suitable class found" MOC note
class QmlProperty : public QObject { Q_OBJECT };

#endif // QMLHELPERS_H
