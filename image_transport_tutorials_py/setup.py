from setuptools import find_packages, setup

package_name = 'image_transport_tutorials_py'

setup(
    name=package_name,
    version='0.0.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
    ],
    install_requires=['setuptools', 'rclpy', 'image_transport_py'],
    zip_safe=True,
    maintainer='tamas.foldi',
    maintainer_email='tfoldi@xsi.hu',
    description='Tutorials for image_transport_py',
    license='Apache-2.0',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            'my_publisher = image_transport_tutorials_py.my_publisher:main',
            'my_subscriber = image_transport_tutorials_py.my_subscriber:main',
        ],
    },
)
