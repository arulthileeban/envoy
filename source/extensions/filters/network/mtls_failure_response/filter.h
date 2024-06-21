#pragma once

#include "envoy/buffer/buffer.h"
#include "envoy/extensions/filters/network/mtls_failure_response/v3/mtls_failure_response.pb.h"
#include "envoy/network/filter.h"
#include "envoy/ssl/context.h"
#include "envoy/stream_info/stream_info.h"

#include "source/common/common/shared_token_bucket_impl.h"
#include "source/extensions/filters/network/common/factory_base.h"

namespace Envoy {
namespace Extensions {
namespace NetworkFilters {
namespace MtlsFailureResponse {

class MtlsFailureResponseFilter : public Network::ReadFilter {
public:
  MtlsFailureResponseFilter(
      const envoy::extensions::filters::network::mtls_failure_response::v3::MtlsFailureResponse&
          config,
      Server::Configuration::FactoryContext& context,
      std::shared_ptr<SharedTokenBucketImpl> token_bucket);

  Network::FilterStatus onData(Buffer::Instance&, bool) override;
  Network::FilterStatus onNewConnection() override { return Network::FilterStatus::Continue; }
  void initializeReadFilterCallbacks(Network::ReadFilterCallbacks& callbacks) override {
    callbacks_ = &callbacks;
  }

private:
  const envoy::extensions::filters::network::mtls_failure_response::v3::MtlsFailureResponse config_;
  Network::ReadFilterCallbacks* callbacks_{};
  std::shared_ptr<SharedTokenBucketImpl> token_bucket_;
};

} // namespace MtlsFailureResponse
} // namespace NetworkFilters
} // namespace Extensions
} // namespace Envoy
