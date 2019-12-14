#pragma once

#include <array>
#include <cstdint>
#include <functional>
#include <sstream>
#include <stdexcept>
#include <vector>

namespace intcode {

enum class Mode { Position = 0, Immediate = 1, Relative = 2 };
enum class ArgMode { Read = 0, Write = 1 };
enum class Opcode { ADD = 1, MUL = 2, IN = 3, OUT = 4, JT = 5, JF = 6, LT = 7, EQ = 8, RBADD = 9, HLT = 99 };

using program_t = std::vector<std::int64_t>;

class VM {
public:
    VM(const program_t& code) : code_(code) {}

    ~VM() = default;

    std::int64_t run(std::int64_t input, std::function<void(std::int64_t)>&& on_out) {
        mem_ = code_;
        ip_ = 0;
        rb_ = 0;

        std::int64_t result = 0;

        while (true) {
            Opcode opcode = decode_opcode(mem_[ip_] % 100);

            // std::cout << "pc: " << ip_ << ", rb: " << rb_ << ", opcode: " << static_cast<int>(opcode) << '\n';

            if (Opcode::HLT == opcode) {
                break;
            }

            auto modes = decode_modes(mem_[ip_] / 100);

            if (Opcode::ADD == opcode) {
                auto arg1 = get_argument(++ip_, modes[0], ArgMode::Read);
                auto arg2 = get_argument(++ip_, modes[1], ArgMode::Read);
                auto arg3 = get_argument(++ip_, modes[2], ArgMode::Write);

                mem_[arg3] = arg1 + arg2;
            } else if (Opcode::MUL == opcode) {
                auto arg1 = get_argument(++ip_, modes[0], ArgMode::Read);
                auto arg2 = get_argument(++ip_, modes[1], ArgMode::Read);
                auto arg3 = get_argument(++ip_, modes[2], ArgMode::Write);

                mem_[arg3] = arg1 * arg2;
            } else if (Opcode::IN == opcode) {
                auto arg = get_argument(++ip_, modes[0], ArgMode::Write);
                mem_[arg] = input;
            } else if (Opcode::OUT == opcode) {
                auto arg = get_argument(++ip_, modes[0], ArgMode::Read);
                on_out(arg);
            } else if (Opcode::JT == opcode) {
                auto arg1 = get_argument(++ip_, modes[0], ArgMode::Read);
                auto arg2 = get_argument(++ip_, modes[1], ArgMode::Read);

                if (arg1) {
                    ip_ = arg2 - 1;
                }
            } else if (Opcode::JF == opcode) {
                auto arg1 = get_argument(++ip_, modes[0], ArgMode::Read);
                auto arg2 = get_argument(++ip_, modes[1], ArgMode::Read);

                if (!arg1) {
                    ip_ = arg2 - 1;
                }
            } else if (Opcode::LT == opcode) {
                auto arg1 = get_argument(++ip_, modes[0], ArgMode::Read);
                auto arg2 = get_argument(++ip_, modes[1], ArgMode::Read);
                auto arg3 = get_argument(++ip_, modes[2], ArgMode::Write);

                mem_[arg3] = (arg1 < arg2) ? 1 : 0;
            } else if (Opcode::EQ == opcode) {
                auto arg1 = get_argument(++ip_, modes[0], ArgMode::Read);
                auto arg2 = get_argument(++ip_, modes[1], ArgMode::Read);
                auto arg3 = get_argument(++ip_, modes[2], ArgMode::Write);

                mem_[arg3] = (arg1 == arg2) ? 1 : 0;
            } else if (Opcode::RBADD == opcode) {
                auto arg = get_argument(++ip_, modes[0], ArgMode::Read);
                rb_ += arg;
            } else {
                std::stringstream ss;
                ss << "Should not be here, but the opcode is wrong: " << (static_cast<std::int64_t>(opcode))
                   << ", ip = " << ip_ << ", rb = " << rb_;
                throw std::runtime_error(ss.str());
            }

            ++ip_;
        }

        return result;
    }

private:
    Opcode decode_opcode(std::int64_t opcode) {
        Opcode oc = static_cast<Opcode>(opcode);

        if (oc < Opcode::ADD || (oc > Opcode::RBADD && oc != Opcode::HLT)) {
            std::stringstream ss;
            ss << "Unknown opcode " << opcode << ", ip = " << ip_ << ", rb = " << rb_;
            throw std::runtime_error(ss.str());
        }

        return oc;
    }

    std::array<Mode, 3> decode_modes(std::int64_t mode) {
        std::array<Mode, 3> modes;

        for (auto& m : modes) {
            m = static_cast<Mode>(mode % 10);

            if (m < Mode::Position || m > Mode::Relative) {
                std::stringstream ss;
                ss << "Unknown mode " << mode << ", ip = " << ip_ << ", rb = " << rb_;
                throw std::runtime_error(ss.str());
            }

            mode /= 10;
        }

        return modes;
    }

    // has side effects
    std::int64_t get_argument(std::uint64_t ip, Mode mode, ArgMode arg_mode) {
        std::int64_t result = mem_[ip];

        if (mode == Mode::Relative) {
            result += rb_;
        }

        if (mode == Mode::Position || mode == Mode::Relative) {
            if (result < 0) {
                std::stringstream ss;
                ss << "Negative memory index " << result << ", ip = " << ip_ << ", rb = " << rb_;
                throw std::runtime_error(ss.str());
            } else if (result >= mem_.size()) {
                // allocate extra memory
                mem_.resize(result + 1, 0);
            }

            if (arg_mode == ArgMode::Read) {
                return mem_[result];
            }
        }

        // immediate mode
        if (mode == Mode::Immediate && arg_mode == ArgMode::Write) {
            std::stringstream ss;
            ss << "Invalid mode for write arg " << result << ", ip = " << ip_ << ", rb = " << rb_;
            throw std::runtime_error(ss.str());
        }

        return result;
    }

private:
    const program_t code_;
    program_t mem_;
    std::uint64_t ip_{0};
    std::uint64_t rb_{0};
};
}  // namespace intcode
