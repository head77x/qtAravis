// QtArvEvaluator.h - GenICam math expression evaluator (ported from Aravis)
#pragma once

#include <QObject>
#include <QHash>
#include <QString>
#include <QVariant>

class QtArvEvaluator : public QObject {
    Q_OBJECT

public:
    explicit QtArvEvaluator(QObject* parent = nullptr);
    ~QtArvEvaluator();

    void setExpression(const QString& expression);
    QString getExpression() const;

    void setConstant(const QString& name, const QString& expression);
    QString getConstant(const QString& name) const;

    void setSubExpression(const QString& name, const QString& expression);
    QString getSubExpression(const QString& name) const;

    void setVariable(const QString& name, double value);
    void setVariable(const QString& name, qint64 value);

    double evaluateAsDouble(bool* ok = nullptr) const;
    qint64 evaluateAsInt64(bool* ok = nullptr) const;

private:
    QString m_expression;
    QHash<QString, QString> m_constants;
    QHash<QString, QString> m_subExpressions;
    QHash<QString, QVariant> m_variables;

    mutable bool m_parsed = false;
    mutable QList<QVariant> m_rpnStack;

    bool parse() const;
    bool evaluate(QVariant* result, bool asDouble) const;
};
