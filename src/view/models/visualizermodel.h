#ifndef VISUALIZERMODEL_H
#define VISUALIZERMODEL_H

#include <QObject>

class VisualizerModel : public QObject
{
    Q_OBJECT
public:
    explicit VisualizerModel(QObject *parent = nullptr);

signals:
};

#endif // VISUALIZERMODEL_H
