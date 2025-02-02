const std = @import("std");

pub fn build(b: *std.Build) void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{.preferred_optimize_mode = .ReleaseSafe});

    const exe = b.addExecutable(.{
        .link_libc = true,
        .name = "tokenizer",
        .target = target,
        .optimize = optimize
    });
    exe.addCSourceFiles(.{
        .root = b.path("src"),
        .files = &.{
            "main.c",
            "c_tokenizer.c",
            "../modules/libcstring/src/c_string.c"
        }
    });

    b.installArtifact(exe);
}