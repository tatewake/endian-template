{
	# This is set globally for "project" level, which is required for "actions", rather than target level
    'targets': [{
		'target_name':	'EndianTests',
		'product_name':	'EndianTests',
		'type':			'executable',
		'mac_bundle':	1,

		'sources': [
			'../../tEndianTests.cc',
			'../../tEndian.h',
		],	# sources

		'include_dirs': [
			'../../',
		],	# include_dirs
	}],	# targets

	'xcode_settings': {
		'SYMROOT': '../../build/<@(OS)',
	}, # xcode_settings

	'conditions': [
		['OS=="ios"', {
			'xcode_settings': {
				'SDKROOT': 'iphoneos',
			}, # xcode_settings
		}],  # OS=="ios"
	],  # conditions

	'target_defaults': {
		'configurations': {

			'debug': {
				'defines': [
					'DEBUG=1',
				], #defines

				'xcode_settings': {
					'ONLY_ACTIVE_ARCH': 'YES',
					'DEAD_CODE_STRIPPING': 'NO',
					'GCC_DYNAMIC_NO_PIC': 'NO',
					'GCC_FAST_MATH': 'NO',
					'GCC_GENERATE_DEBUGGING_SYMBOLS': 'YES',
					'GCC_OPTIMIZATION_LEVEL': '0',
					'GCC_STRICT_ALIASING': 'NO',
					'GCC_UNROLL_LOOPS': 'NO',
					'LD_NO_PIE': 'NO',
				}, # xcode_settings

				'msvs_configuration_attributes': {
					'IntermediateDirectory': '$(SolutionDir)..\\..\\build\\win\\$(ProjectName).build\\$(Configuration)\\obj\\',
					'OutputDirectory': '$(SolutionDir)..\\..\\build\\win\\$(Configuration)\\',
				}, # msvs_configuration_attributes

				'msvs_settings': {
					'VCLinkerTool': {
						'GenerateDebugInformation': 'true',
					},  # VCLinkerTool
				},  # msvs_settings
			}, # debug
		}, # configurations

		'include_dirs': [
			'../../',
		 ],  # include_dirs

		'conditions': [

			['OS=="win"', {
				'defines': [
					'WIN32',
				],  # defines
			}], # OS=="win"
	
			['OS=="mac"', {
				'xcode_settings': {
					'ARCHS': '$(ARCHS_STANDARD_32_64_BIT)',
					'MACOSX_DEPLOYMENT_TARGET': '10.9',
				},
			}], # OS=="mac"

			['OS=="ios"', {
				'xcode_settings': {
					'TARGETED_DEVICE_FAMILY': '1,2',
					'CODE_SIGN_IDENTITY': 'iPhone Developer',
					'IPHONEOS_DEPLOYMENT_TARGET': '8.0',
				},
			}], # OS=="ios"
		],   # conditions
	}, # target_defaults
}
