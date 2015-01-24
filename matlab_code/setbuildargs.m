function setbuildargs(buildInfo)
% The example being compiled requires threading support.
% The flag requests that the thread library be included
% in the build

linkFlags = {'-soname,libfft_from_matlab.so'};
addCompileFlags(buildInfo, linkFlags);
%linkFlags = {'-pthread'};
%addLinkFlags(buildInfo, linkFlags);