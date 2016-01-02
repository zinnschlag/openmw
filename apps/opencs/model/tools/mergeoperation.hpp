#ifndef CSM_TOOLS_MERGEOPERATION_H
#define CSM_TOOLS_MERGEOPERATION_H

#include <memory>

#include <components/to_utf8/to_utf8.hpp>

#include "../doc/operation.hpp"

#include "mergestate.hpp"

namespace CSMDoc
{
    class Document;
}

namespace CSMTools
{
    class MergeOperation : public CSMDoc::Operation
    {
            Q_OBJECT

            MergeState mState;

        public:

            MergeOperation (CSMDoc::Document& document, ToUTF8::FromType encoding);

            /// \attention Do not call this function while a merge is running.
            void setTarget (std::auto_ptr<CSMDoc::Document> document);

        protected slots:

            virtual void operationDone();

        signals:

            /// \attention When this signal is emitted, *this hands over the ownership of the
            /// document. This signal must be handled to avoid a leak.
            void mergeDone (CSMDoc::Document *document);

    };
}

#endif
