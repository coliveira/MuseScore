//=============================================================================
//  MusE Reader
//  Music Score Reader
//  $Id$
//
//  Copyright (C) 2010 Werner Schweer
//
//  This program is free software; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License version 2.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
//=============================================================================

#ifndef __OMR_H__
#define __OMR_H__

#include "config.h"

class OmrView;
class Xml;
class Pdf;
class OmrPage;
class Ocr;
class Score;
class ScoreView;

#ifdef OMR

//---------------------------------------------------------
//   Omr
//---------------------------------------------------------

class Omr {
      QString _path;
      double _spatium;
      double _dpmm;
      Pdf* _doc;
      QList<OmrPage*> _pages;
      Ocr* _ocr;
      Score* _score;

      static void initUtils();

      void process1(int page);

   public:
      Omr(Score*);
      Omr(const QString& path, Score*);

      static char bitsSetTable[256];

      bool readPdf();
      int pagesInDocument() const;
      int numPages() const                 { return _pages.size();          }
      OmrPage* page(int idx)               { return _pages[idx];            }
      OmrView* newOmrView(ScoreView*);
      const QList<OmrPage*>& pages() const { return _pages; }
#ifdef OCR
      Ocr* ocr() const                     { return _ocr; }
#endif
      void write(Xml&) const;
      void read(QDomElement e);

      double spatiumMM() const;           // spatium in millimeter
      double spatium() const               { return _spatium;   }
      void setSpatium(double val)          { _spatium = val;    }
      double dpmm() const                  { return _dpmm;      }
      void setDpmm(double val)             { _dpmm = val;       }
      double staffDistance() const;
      double systemDistance() const;
      Score* score() const                 { return _score;     }
      const QString& path() const          { return _path;      }
      void process();
      };

#else
//---------------------------------------------------------
//   Omr
//---------------------------------------------------------

class Omr {
      QString _path;
      QList<OmrPage*> _pages;

   public:
      Omr(Score*)                          {}
      Omr(const QString&, Score*)          {}
      bool readPdf()                       { return false; }
      int pagesInDocument() const          { return 0; }
      int numPages() const                 { return 0; }
      OmrPage* page(int)                   { return 0; }
      const QList<OmrPage*>& pages() const { return _pages; }
      OmrView* newOmrView(ScoreView*)      { return 0; }
#ifdef OCR
      Ocr* ocr() const                     { return 0; }
#endif
      void write(Xml&) const               {}
      void read(QDomElement)               {}

      double spatiumMM() const             { return 0; }
      double spatium() const               { return 0; }
      double dpmm() const                  { return 0; }
      double staffDistance() const         { return 0; }
      double systemDistance() const        { return 0; }
      Score* score() const                 { return 0; }
      const QString& path() const          { return _path; }
      };

#endif
#endif
