#pragma once
/****************************************************************************
**
** Copyright (C) 2024 David C. Partridge
**
** BSD License Usage
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of DeepSkyStacker nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
**
****************************************************************************/
#include <QFileDialog>
#include "DSSCommon.h"

class QCheckBox;
class QGroupBox;
class QHBoxLayout;
class QRadioButton;
class QVBoxLayout;

namespace DSS
{
	class SavePicture final : public QFileDialog
	{
		Q_OBJECT

	public:
		SavePicture(QWidget* parent = nullptr, const QString& caption = QString(), const QString& directory = QString(), const QString& filter = QString());

		~SavePicture() = default;

		SavePicture(const SavePicture&) = delete;
		SavePicture(SavePicture&&) = delete;
		SavePicture& operator=(const SavePicture& rhs) = delete;

		void retranslateUi(QWidget*);

		void connectSignalsToSlots();

		inline void setCompression(const TIFFCOMPRESSION comp)
		{
			compression_ = comp;
			switch (comp)
			{
			case TC_NONE:
				compressionNone->setChecked(true);
				break;
			case TC_DEFLATE:
				compressionZIP->setChecked(true);
				break;
			case TC_LZW:
				compressionLZW->setChecked(true);
				break;
			}
		}

		inline TIFFCOMPRESSION compression() const { return compression_; }

		inline void setApply(const bool apply)
		{
			apply_ = apply;
			if (apply)
			{
				applyAdjustments->setChecked(true);
			}
			else
			{
				embedAdjustments->setChecked(true);
			}

		}

		inline bool apply() const  { return apply_; }

		void setUseRect(bool use)
		{
			useRectangle->setEnabled(true);
			useRect_ = use;

		}

		inline bool useRect() const { return useRect_; }

	private:
		QGroupBox* compressionGroup;
		QHBoxLayout* compressionLayout;
		QRadioButton* compressionNone;
		QRadioButton* compressionZIP;
		QRadioButton* compressionLZW;

		QGroupBox* optionsGroup;
		QVBoxLayout* optionsLayout;
		QRadioButton* applyAdjustments;
		QRadioButton* embedAdjustments;
		QCheckBox* useRectangle;

		QString embedText;
		QString noAdjustments;

		TIFFCOMPRESSION compression_;
		bool apply_;
		bool useRect_;

	public slots:
		void onFilter(const QString& filter);

	private slots:
		void onCompressionNone(bool checked);
		void onCompressionZIP(bool checked);
		void onCompressionLZW(bool checked);
		void onApply(bool checked);
		void onEmbed(bool checked);
		void onRect(bool checked);

	};
}

