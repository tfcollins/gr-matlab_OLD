function builder_lib()


cfg = coder.config('dll');
cfg.TargetLang='C++';
%cfg.PostCodeGenCommand = 'setbuildargs(buildInfo)';
result = codegen('-config','cfg','fft_from_matlab','-o','libfft_from_matlab.so');
if result.summary.passed
    system(['cp ',pwd,'/codegen/dll/fft_from_matlab/fft_from_matlab.so ../lib/']);
    system(['cp ',pwd,'/codegen/dll/fft_from_matlab/fft_from_matlab.h ../include/']);
    system(['cp ',pwd,'/codegen/dll/fft_from_matlab/fft_from_matlab_types.h ../include/']);
        system(['cp ',pwd,'/codegen/dll/fft_from_matlab/rtwtypes.h ../include/']);
    system(['rm -rf ',pwd,'/codegen']);
else
    disp('Build failed');
end

end
