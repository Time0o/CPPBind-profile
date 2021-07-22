#!/usr/bin/env python3

import subprocess
import argparse
import os

if __name__ == '__main__':
    class ToWrap:
        def __init__(self,
                     path,
                     include_dir=None,
                     enums=None,
                     variables=None,
                     functions=None,
                     records=None,
                     template_instantiations=None):

            self._path = os.path.join(path)
            self._include_dir = include_dir
            self._enums = enums
            self._variables = variables
            self._functions = functions
            self._records = records
            self._template_instantiations = template_instantiations

        def args(self):
            args = [self._path]

            if self._include_dir is not None:
                args += [f'--extra-arg=-I{self._include_dir}']

            if self._enums is not None:
                for e in self._enums:
                    args += ['--wrap-rule', f'enum:hasName("{e}")']

            if self._variables is not None:
                for v in self._variables:
                    args += ['--wrap-rule', f'variable:hasName("{v}")']

            if self._functions is not None:
                for f in self._functions:
                    args += ['--wrap-rule', f'function:hasName("{f}")']

            if self._records is not None:
                for r in self._records:
                    args += ['--wrap-rule', f'record:hasName("{r}")']

            if self._template_instantiations is not None:
                args += ['--template-instantiations',
                         self._template_instantiations]

            return args

    to_wrap_list = [
        ToWrap('api.h',
               records=['Kobject', 'Cap_base', 'Cap'],
               template_instantiations='api.tcc'),
    ]

    for backend in ['c', 'rust', 'lua']:
        cppbind_args = [
            'cppbind',
            '--extra-arg=-I.',
            '--backend', backend
        ]

        for to_wrap in to_wrap_list:
            cppbind_args += to_wrap.args()

        cppbind_args += [
            '--wrap-macro-constants',
            '--wrap-skip-unwrappable',
            '--wrap-noexcept',
            '--output-directory', 'bind',
            '--output-cpp-header-extension', '.h',
            '--output-cpp-source-extension', '.cc',
            '--lua-include-cpp',
            '--verbosity', '2',
            '--'
        ]

        subprocess.run(cppbind_args, check=True)
