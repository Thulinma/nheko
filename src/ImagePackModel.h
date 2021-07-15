// SPDX-FileCopyrightText: 2021 Nheko Contributors
//
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <QAbstractListModel>

#include <mtx/events/mscs/image_packs.hpp>

class ImagePackModel : public QAbstractListModel
{
        Q_OBJECT
public:
        enum Roles
        {
                Url = Qt::UserRole,
                ShortCode,
                Body,
                PackName,
                OriginalRow,
        };

        ImagePackModel(const std::string &roomId, bool stickers, QObject *parent = nullptr);
        QHash<int, QByteArray> roleNames() const override;
        int rowCount(const QModelIndex &parent = QModelIndex()) const override
        {
                (void)parent;
                return (int)images.size();
        }
        QVariant data(const QModelIndex &index, int role) const override;

        mtx::events::msc2545::PackImage imageAt(int row)
        {
                if (row < 0 || static_cast<size_t>(row) >= images.size())
                        return {};
                return images.at(static_cast<size_t>(row)).image;
        }

private:
        std::string room_id;

        struct ImageDesc
        {
                QString shortcode;
                QString packname;

                mtx::events::msc2545::PackImage image;
        };

        std::vector<ImageDesc> images;
};
