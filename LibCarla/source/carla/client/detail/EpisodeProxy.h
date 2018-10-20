// Copyright (c) 2017 Computer Vision Center (CVC) at the Universitat Autonoma
// de Barcelona (UAB).
//
// This work is licensed under the terms of the MIT license.
// For a copy, see <https://opensource.org/licenses/MIT>.

#pragma once

#include "carla/AtomicSharedPtr.h"

namespace carla {
namespace client {
namespace detail {

  class Simulator;

  struct EpisodeProxyPointerType {
    using Shared = std::shared_ptr<Simulator>;
    using Strong = AtomicSharedPtr<Simulator>;
    using Weak = std::weak_ptr<Simulator>;
  };

  /// Provides access to the Simulator during a given episode. After the episode
  /// is ended any access to the simulator throws an std::runtime_error.
  template <typename PointerT>
  class EpisodeProxyImpl {
  public:

    using SharedPtrType = EpisodeProxyPointerType::Shared;

    EpisodeProxyImpl() = default;

    EpisodeProxyImpl(SharedPtrType simulator);

    SharedPtrType TryLock() const;

    /// Same as TryLock but never return nullptr.
    ///
    /// @throw std::runtime_error if episode is gone.
    SharedPtrType Lock() const;

    void Clear();

  private:

    size_t _episode_id;

    PointerT _simulator;
  };

  using EpisodeProxy = EpisodeProxyImpl<EpisodeProxyPointerType::Strong>;

  using WeakEpisodeProxy = EpisodeProxyImpl<EpisodeProxyPointerType::Weak>;

} // namespace detail
} // namespace client
} // namespace carla